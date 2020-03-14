#include <iomanip>

#include "esp.h"
#include "autowall.h"
#include "../fonts.h"
#include "../settings.h"
#include "../interfaces.h"
#include "../Utils/draw.h"
#include "../Utils/math.h"
#include "../Utils/entity.h"
#include "../Utils/bonemaps.h"
#include "../Utils/xorstring.h"
#include "../Hooks/hooks.h"

#include "../ATGUI/texture.h"
#include "../Resources/tux.h"

#include <climits>
#include <deque>
#include <mutex>

/* The engine->WorldToScreenMatrix() function can't be called at all times
 * So this is Updated in the Paint Hook for us */
VMatrix vMatrix;

Vector2D barsSpacing = Vector2D( 0, 0 );

struct Footstep {
    Footstep( Vector &pos, long expireAt ){
        position = pos;
        expiration = expireAt;
    }
    long expiration;
    Vector position;
};

std::mutex footstepMutex;
std::deque<Footstep> playerFootsteps[64]; // entIndex -> Footstep.

QAngle viewanglesBackup;

const char* ESP::ranks[] = {
		"Unranked",
		"Silver I",
		"Silver II",
		"Silver III",
		"Silver IV",
		"Silver Elite",
		"Silver Elite Master",

		"Gold Nova I",
		"Gold Nova II",
		"Gold Nova III",
		"Gold Nova Master",
		"Master Guardian I",
		"Master Guardian II",

		"Master Guardian Elite",
		"Distinguished Master Guardian",
		"Legendary Eagle",
		"Legendary Eagle Master",
		"Supreme Master First Class",
		"The Global Elite"
};

bool dzShouldDraw(C_BaseEntity* ent, C_BasePlayer* localplayer) // Ghetto way to fix a CTD.
{
	if (!localplayer || !ent || !localplayer->GetAlive())
		return false;
	return !(Settings::ESP::DangerZone::drawDistEnabled &&
			(localplayer->GetVecOrigin().DistTo(ent->GetVecOrigin()) > Settings::ESP::DangerZone::drawDist));
}

static void CheckActiveSounds() {
    static CUtlVector<SndInfo_t> sounds; // this has to be static.
    char buf[PATH_MAX];
    static int lastSoundGuid = 0;  // the Unique sound playback ID's increment. It does not get reset to 0
    sound->GetActiveSounds( sounds );
    for ( int i = 0; i < sounds.Count(); i++ ){
        if( sounds[i].m_nSoundSource <= 0 || sounds[i].m_nSoundSource > 63 ) // environmental sounds or out of bounds.
            continue;
        if( !sounds[i].m_pOrigin ) // no location
            continue;
        if( sounds[i].m_nGuid <= lastSoundGuid ) // same sound we marked last time
            continue;
        if( sounds[i].m_nSoundSource == engine->GetLocalPlayer() )
            continue;

        if( !fileSystem->String( sounds[i].m_filenameHandle, buf, sizeof( buf ) ) )
            continue;
        if ( buf[0] != '~' )
            continue;

        if ( strstr( buf, XORSTR( "player/land" ) ) != nullptr ){
            {
                std::unique_lock<std::mutex> lock( footstepMutex );
                playerFootsteps[sounds[i].m_nSoundSource].emplace_back( *sounds[i].m_pOrigin, ( Util::GetEpochTime( ) + Settings::ESP::Sounds::time ) );
            } // RAII mutex lock
            lastSoundGuid = sounds[i].m_nGuid;
        } else if ( strstr( buf, XORSTR( "footstep" ) ) != nullptr ){
            {
                std::unique_lock<std::mutex> lock( footstepMutex );
                playerFootsteps[sounds[i].m_nSoundSource].emplace_back( *sounds[i].m_pOrigin, ( Util::GetEpochTime( ) + Settings::ESP::Sounds::time ) );
            } // RAII mutex lock
            lastSoundGuid = sounds[i].m_nGuid;
        }
    }
    // GetActiveSounds allocates new memory to our CUtlVector every time for some reason.
    sounds.m_Size = 0; // Setting this to 0 makes it use the same memory each time instead of grabbing more.
}

// credits to Casual_Hacker from UC for this method (I modified it a lil bit)
static float GetArmourHealth(float flDamage, int ArmorValue)
{
	float flCurDamage = flDamage;

	if (flCurDamage == 0.0f || ArmorValue == 0)
		return flCurDamage;

	float flArmorRatio = 0.5f;
	float flArmorBonus = 0.5f;
	float flNew = flCurDamage * flArmorRatio;
	float flArmor = (flCurDamage - flNew) * flArmorBonus;

	if (flArmor > ArmorValue)
	{
		flArmor = ArmorValue * (1.0f / flArmorBonus);
		flNew = flCurDamage - flArmor;
	}

	return flNew;
}

static bool GetBox( C_BaseEntity* entity, int& x, int& y, int& w, int& h ) {
	// Variables
	Vector vOrigin, min, max;
	Vector flb, brt, blb, frt, frb, brb, blt, flt; // think of these as Front-Left-Bottom/Front-Left-Top... Etc.
	float left, top, right, bottom;

	// Get the locations
	vOrigin = entity->GetVecOrigin();
	min = entity->GetCollideable()->OBBMins() + vOrigin;
	max = entity->GetCollideable()->OBBMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector( min.x, min.y, min.z ),
						Vector( min.x, max.y, min.z ),
						Vector( max.x, max.y, min.z ),
						Vector( max.x, min.y, min.z ),
						Vector( max.x, max.y, max.z ),
						Vector( min.x, max.y, max.z ),
						Vector( min.x, min.y, max.z ),
						Vector( max.x, min.y, max.z ) };

	// Get screen positions
	if ( debugOverlay->ScreenPosition( points[3], flb ) || debugOverlay->ScreenPosition( points[5], brt )
		 || debugOverlay->ScreenPosition( points[0], blb ) || debugOverlay->ScreenPosition( points[4], frt )
		 || debugOverlay->ScreenPosition( points[2], frb ) || debugOverlay->ScreenPosition( points[1], brb )
		 || debugOverlay->ScreenPosition( points[6], blt ) || debugOverlay->ScreenPosition( points[7], flt ) )
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for ( int i = 1; i < 8; i++ ) {
		if ( left > arr[i].x )
			left = arr[i].x;
		if ( bottom < arr[i].y )
			bottom = arr[i].y;
		if ( right < arr[i].x )
			right = arr[i].x;
		if ( top > arr[i].y )
			top = arr[i].y;
	}

	// Width / height
	x = ( int ) left;
	y = ( int ) top;
	w = ( int ) ( right - left );
	h = ( int ) ( bottom - top );

	return true;
}


ImColor ESP::GetESPPlayerColor(C_BasePlayer* player, bool visible)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return ImColor(255, 255, 255, 255);

	ImColor playerColor;

	if (player == localplayer)
	{
		playerColor = Settings::ESP::localplayerColor.Color(player);
	}
	else
	{
		if (Settings::ESP::teamColorType == TeamColorType::RELATIVE)
		{
			if (!Entity::IsTeamMate(player, localplayer))
			{
				if (visible)
					playerColor = Settings::ESP::enemyVisibleColor.Color(player);
				else
					playerColor = Settings::ESP::enemyColor.Color(player);
			}
			else
			{
				if (visible)
					playerColor = Settings::ESP::allyVisibleColor.Color(player);
				else
					playerColor = Settings::ESP::allyColor.Color(player);
			}
		}
		else if (Settings::ESP::teamColorType == TeamColorType::ABSOLUTE)
		{
			if (player->GetTeam() == TeamID::TEAM_TERRORIST)
			{
				if (visible)
					playerColor = Settings::ESP::tVisibleColor.Color(player);
				else
					playerColor = Settings::ESP::tColor.Color(player);
			}
			else if (player->GetTeam() == TeamID::TEAM_COUNTER_TERRORIST)
			{
				if (visible)
					playerColor = Settings::ESP::ctVisibleColor.Color(player);
				else
					playerColor = Settings::ESP::ctColor.Color(player);
			}
		}
	}

	if (player->GetImmune())
	{
		playerColor.Value.x *= 0.45f;
		playerColor.Value.y *= 0.45f;
		playerColor.Value.z *= 0.45f;
	}

	return playerColor;
}

bool ESP::WorldToScreen( const Vector &origin, ImVec2 * const screen ) {
	float w = vMatrix[3][0] * origin.x
			  + vMatrix[3][1] * origin.y
			  + vMatrix[3][2] * origin.z
			  + vMatrix[3][3];

	if ( w < 0.01f ) // Is Not in front of our player
		return false;

	float width = (float)Paint::engineWidth;
	float height = (float)Paint::engineHeight;

	float halfWidth = width / 2;
	float halfHeight = height / 2;

	float inverseW = 1 / w;

	screen->x = halfWidth +
				(0.5f * ((vMatrix[0][0] * origin.x +
						  vMatrix[0][1] * origin.y +
						  vMatrix[0][2] * origin.z +
						  vMatrix[0][3]) * inverseW) * width + 0.5f);

	screen->y = halfHeight -
				(0.5f * ((vMatrix[1][0] * origin.x +
						  vMatrix[1][1] * origin.y +
						  vMatrix[1][2] * origin.z +
						  vMatrix[1][3]) * inverseW) * height + 0.5f);
	return true;
}

static void DrawBox( ImColor color, int x, int y, int w, int h, C_BaseEntity* entity ) {
	if ( Settings::ESP::Boxes::type == BoxType::FRAME_2D ) {
		int VertLine = w / 3;
		int HorzLine = h / 3;
		int squareLine = std::min( VertLine, HorzLine );

		// top-left corner / color
		Draw::AddRect( x, y, x + squareLine, y + 1, color );
		Draw::AddRect( x, y, x + 1, y + squareLine, color );



		// top-left corner / missing edges
		Draw::AddRect( x + squareLine, y - 1, x + squareLine + 1, y + 2, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x - 1, y + squareLine, x + 2, y + squareLine + 1, ImColor( 10, 10, 10, 190 ) );


		// top-right corner / color
		Draw::AddRect( x + w - squareLine, y, x + w, y + 1, color );
		Draw::AddRect( x + w - 1, y, x + w, y + squareLine, color );



		// top-right corner / missing edges
		Draw::AddRect( x + w - squareLine - 1, y - 1, x + w - squareLine, y + 2, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x + w - 2, y + squareLine, x + w + 1, y + squareLine + 1, ImColor( 10, 10, 10, 190 ) );


		// bottom-left corner / color
		Draw::AddRect( x, y + h - 1, x + squareLine, y + h, color );
		Draw::AddRect( x, y + h - squareLine, x + 1, y + h, color );



		// bottom-left corner / missing edges
		Draw::AddRect( x + squareLine, y + h - 2, x + squareLine + 1, y + h + 1, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x - 1, y + h - squareLine - 1, x + 2, y + h - squareLine, ImColor( 10, 10, 10, 190 ) );


		// bottom-right corner / color
		Draw::AddRect( x + w - squareLine, y + h - 1, x + w, y + h, color );
		Draw::AddRect( x + w - 1, y + h - squareLine, x + w, y + h, color );


		// bottom-right corner / missing edges
		Draw::AddRect( x + w - squareLine, y + h - 2, x + w - squareLine + 1, y + h + 1, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x + w - 2, y + h - squareLine - 1, x + w + 1, y + h - squareLine, ImColor( 10, 10, 10, 190 ) );
	} else if ( Settings::ESP::Boxes::type == BoxType::FLAT_2D ) {
		int VertLine = ( int ) ( w * 0.33f );
		int HorzLine = ( int ) ( h * 0.33f );
		int squareLine = std::min( VertLine, HorzLine );

		// top-left corner / color
		Draw::AddRect( x, y, x + squareLine, y + 1, color );
		Draw::AddRect( x, y, x + 1, y + squareLine, color );

		// top-left corner / missing edges
		Draw::AddRect( x + squareLine, y - 1, x + squareLine + 1, y + 2, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x - 1, y + squareLine, x + 2, y + squareLine + 1, ImColor( 10, 10, 10, 190 ) );


		// top-right corner / color
		Draw::AddRect( x + w - squareLine, y, x + w, y + 1, color );
		Draw::AddRect( x + w - 1, y, x + w, y + squareLine, color );

		// top-right corner / missing edges
		Draw::AddRect( x + w - squareLine - 1, y - 1, x + w - squareLine, y + 2, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x + w - 2, y + squareLine, x + w + 1, y + squareLine + 1, ImColor( 10, 10, 10, 190 ) );


		// bottom-left corner / color
		Draw::AddRect( x, y + h - 1, x + squareLine, y + h, color );
		Draw::AddRect( x, y + h - squareLine, x + 1, y + h, color );

		// bottom-left corner / missing edges
		Draw::AddRect( x + squareLine, y + h - 2, x + squareLine + 1, y + h + 1, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x - 1, y + h - squareLine - 1, x + 2, y + h - squareLine, ImColor( 10, 10, 10, 190 ) );


		// bottom-right corner / color
		Draw::AddRect( x + w - squareLine, y + h - 1, x + w, y + h, color );
		Draw::AddRect( x + w - 1, y + h - squareLine, x + w, y + h, color );

		// bottom-right corner / missing edges
		Draw::AddRect( x + w - squareLine, y + h - 2, x + w - squareLine + 1, y + h + 1, ImColor( 10, 10, 10, 190 ) );
		Draw::AddRect( x + w - 2, y + h - squareLine - 1, x + w + 1, y + h - squareLine, ImColor( 10, 10, 10, 190 ) );

		Draw::AddRectFilled( x, y, x + w, y + h, ImColor( color.Value.x, color.Value.y, color.Value.z, 21 * (1.0f/255.0f) ) );
	} else if ( Settings::ESP::Boxes::type == BoxType::BOX_3D ) {
		Vector vOrigin = entity->GetVecOrigin();
		Vector min = entity->GetCollideable()->OBBMins() + vOrigin;
		Vector max = entity->GetCollideable()->OBBMaxs() + vOrigin;

		Vector points[] = { Vector( min.x, min.y, min.z ),
							Vector( min.x, max.y, min.z ),
							Vector( max.x, max.y, min.z ),
							Vector( max.x, min.y, min.z ),
							Vector( min.x, min.y, max.z ),
							Vector( min.x, max.y, max.z ),
							Vector( max.x, max.y, max.z ),
							Vector( max.x, min.y, max.z ) };

		int edges[12][2] = {
				{ 0, 1 },
				{ 1, 2 },
				{ 2, 3 },
				{ 3, 0 },
				{ 4, 5 },
				{ 5, 6 },
				{ 6, 7 },
				{ 7, 4 },
				{ 0, 4 },
				{ 1, 5 },
				{ 2, 6 },
				{ 3, 7 },
		};

		for ( const auto edge : edges ) {
			Vector p1, p2;
			if ( debugOverlay->ScreenPosition( points[edge[0]], p1 ) || debugOverlay->ScreenPosition( points[edge[1]], p2 ) )
				return;
			Draw::AddLine( p1.x, p1.y, p2.x, p2.y, color );
		}
	} /*else if ( Settings::ESP::Boxes::type == BoxType::HITBOXES )  credits to 1337floesen - https://www.unknowncheats.me/forum/counterstrike-global-offensive/157557-drawing-hitboxes.html */ //{
	/*static std::map<int, long> playerDrawTimes;
    if ( playerDrawTimes.find( entity->GetIndex() ) == playerDrawTimes.end() ) { // haven't drawn this player yet
        playerDrawTimes[entity->GetIndex()] = Util::GetEpochTime();
    }

    matrix3x4_t matrix[128];

    if ( !entity->SetupBones( matrix, 128, 0x00000100, globalVars->curtime ) )
        return;

    studiohdr_t* hdr = modelInfo->GetStudioModel( entity->GetModel() );
    mstudiohitboxset_t* set = hdr->pHitboxSet( 0 ); // :^)

    long diffTime = Util::GetEpochTime() - playerDrawTimes.at( entity->GetIndex() );
    if ( diffTime >= 12 ) {
        for ( int i = 0; i < set->numhitboxes; i++ ) {
            mstudiobbox_t* hitbox = set->pHitbox( i );
            if ( !hitbox ) {
                continue;
            }
            Vector vMin, vMax;
            Math::VectorTransform( hitbox->bbmin, matrix[hitbox->bone], vMin );
            Math::VectorTransform( hitbox->bbmax, matrix[hitbox->bone], vMax );

            debugOverlay->DrawPill( vMin, vMax, hitbox->radius, color.r, color.g, color.b, 0.025f, color.a, false );
        }
        playerDrawTimes[entity->GetIndex()] = Util::GetEpochTime();
    }
}*/
}

static void DrawSprite( int x, int y, int w, int h, C_BaseEntity* entity ){
	if ( Settings::ESP::Sprite::type == SpriteType::SPRITE_TUX ) {
		static Texture sprite(tux_rgba, tux_width, tux_height);

		sprite.Draw(x, y, ((float)h/tux_height)*tux_width, h);
	}
	// TODO: Handle other sprites
}

static void DrawEntity( C_BaseEntity* entity, const char* string, ImColor color ) {
	int x, y, w, h;
	if ( !GetBox( entity, x, y, w, h ) )
		return;

	DrawBox( color, x, y, w, h, entity );
	Vector2D nameSize = Draw::GetTextSize( string, esp_font );
	Draw::AddText(( int ) ( x + ( w / 2 ) - ( nameSize.x / 2 ) ), y + h + 2, string, color );
}
static void DrawSkeleton( C_BasePlayer* player, C_BasePlayer* localplayer ) {
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel( player->GetModel() );
	if ( !pStudioModel )
		return;

	static matrix3x4_t pBoneToWorldOut[128];
	if ( !player->SetupBones( pBoneToWorldOut, 128, 256, 0 ) )
		return;

	for ( int i = 0; i < pStudioModel->numbones; i++ ) {
		mstudiobone_t* pBone = pStudioModel->pBone( i );
		if ( !pBone || !( pBone->flags & 256 ) || pBone->parent == -1 )
			continue;

		Vector vBonePos1;
		if ( debugOverlay->ScreenPosition( Vector( pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3] ), vBonePos1 ) )
			continue;

		Vector vBonePos2;
		if ( debugOverlay->ScreenPosition( Vector( pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3] ), vBonePos2 ) )
			continue;

		Draw::AddLine( vBonePos1.x, vBonePos1.y, vBonePos2.x, vBonePos2.y, Entity::IsTeamMate(player, localplayer) ? Settings::ESP::Skeleton::allyColor.Color() : Settings::ESP::Skeleton::enemyColor.Color());
	}
}
static void DrawBulletTrace( C_BasePlayer* player ) {
	Vector src3D, dst3D, forward;
	Vector src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	Math::AngleVectors( *player->GetEyeAngles(), forward );
	filter.pSkip = player;
	src3D = player->GetEyePosition();
	dst3D = src3D + ( forward * 8192 );

	ray.Init( src3D, dst3D );

	trace->TraceRay( ray, MASK_SHOT, &filter, &tr );

	if ( debugOverlay->ScreenPosition( src3D, src ) || debugOverlay->ScreenPosition( tr.endpos, dst ) )
		return;

	Draw::AddLine( src.x, src.y, dst.x, dst.y, ESP::GetESPPlayerColor( player, true ) );
	Draw::AddRectFilled( ( int ) ( dst.x - 3 ), ( int ) ( dst.y - 3 ), 6, 6, ESP::GetESPPlayerColor( player, false ) );
}
static void DrawTracer( C_BasePlayer* player ) {
	Vector src3D;
	Vector src;
	src3D = player->GetVecOrigin() - Vector( 0, 0, 0 );

	if ( debugOverlay->ScreenPosition( src3D, src ) )
		return;

	int x = Paint::engineWidth / 2;
	int y = 0;

	if ( Settings::ESP::Tracers::type == TracerType::CURSOR )
		y = Paint::engineHeight / 2;
	else if ( Settings::ESP::Tracers::type == TracerType::BOTTOM )
		y = Paint::engineHeight;

	bool bIsVisible = Entity::IsVisible( player, BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck );
	Draw::AddLine( ( int ) ( src.x ), ( int ) ( src.y ), x, y, ESP::GetESPPlayerColor( player, bIsVisible ) );
}
static void DrawAimbotSpot( ) {
	C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
	if ( !localplayer || !localplayer->GetAlive() ){
		Settings::Debug::AutoAim::target = {0,0,0};
		return;
	}
	if ( !Settings::Aimbot::AutoAim::enabled || !Settings::Aimbot::enabled ){
		Settings::Debug::AutoAim::target = {0,0,0};
		return;
	}
	if ( Settings::Debug::AutoAim::target.IsZero() )
		return;

	Vector spot2D;
	if( debugOverlay->ScreenPosition( Settings::Debug::AutoAim::target, spot2D) )
		return;

	Draw::AddLine( Paint::engineWidth / 2, Paint::engineHeight / 2, spot2D.x, spot2D.y, ImColor( 45, 235, 60 ) );
	Draw::AddCircle( Paint::engineWidth / 2, Paint::engineHeight / 2, 1, ImColor( 45, 235, 60 ) );
	Draw::AddCircle( spot2D.x, spot2D.y, 1, ImColor( 45, 235, 60 ) );

    Vector start2D = Vector(0,0,0);
    Vector end2D;
    if( !debugOverlay->ScreenPosition( lastRayEnd, end2D ) ){
        Draw::AddLine( start2D.x, start2D.y, end2D.x, end2D.y, ImColor( 255, 25, 25, 255 ) );
    }
}
static void DrawBoneMap( C_BasePlayer* player ) {
	static Vector bone2D;
	static Vector bone3D;
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel( player->GetModel() );

	if( !pStudioModel )
		return;

	for( int i = 1; i < pStudioModel->numbones; i++ ){
		bone3D = player->GetBonePosition( i );
        mstudiobone_t* pBone = pStudioModel->pBone( i );
		if( !pBone )
			continue;

        if ( debugOverlay->ScreenPosition( bone3D, bone2D ) )
			continue;
		if( Settings::Debug::BoneMap::justDrawDots ){
			Draw::AddCircleFilled( bone2D.x, bone2D.y, 2.0f, ImColor( 255, 0, 255, 255 ), 10 );
		} else {
			char buffer[72];
			snprintf(buffer, 72, "%d - %s", i, pBone->pszName());
			Draw::AddText( bone2D.x, bone2D.y,buffer, ImColor( 255, 0, 255, 255 ) );
		}
	}
	IEngineClient::player_info_t entityInformation;
	engine->GetPlayerInfo( player->GetIndex(), &entityInformation );
	cvar->ConsoleDPrintf( XORSTR( "(%s)-ModelName: %s, numBones: %d\n" ), entityInformation.name, pStudioModel->name, pStudioModel->numbones );
}
static void DrawAutoWall(C_BasePlayer *player) {
	const std::unordered_map<int, int> *modelType = BoneMaps::GetModelTypeBoneMap(player);
	for( int i = 0; i < 31; i++ )
	{
		auto bone = modelType->find(i);
		if( bone == modelType->end() || bone->second <= BONE_INVALID )
			continue;
		Vector bone2D;
		Vector bone3D = player->GetBonePosition(bone->second);
		if ( debugOverlay->ScreenPosition( bone3D, bone2D ) )
			continue;

		Autowall::FireBulletData data;
		int damage = (int)Autowall::GetDamage( bone3D, !Settings::Aimbot::friendly, data );
		char buffer[4];
		snprintf(buffer, sizeof(buffer), "%d", damage);
		Draw::AddText( bone2D.x, bone2D.y, buffer, ImColor( 255, 0, 255, 255 ) );
	}
	return;
	matrix3x4_t matrix[128];

	if( !player->SetupBones(matrix, 128, 0x100, 0.f) )
		return;
	model_t *pModel = player->GetModel();
	if( !pModel )
		return;

	studiohdr_t *hdr = modelInfo->GetStudioModel(pModel);
	if( !hdr )
		return;

	mstudiobbox_t *bbox = hdr->pHitbox((int)Hitbox::HITBOX_HEAD, 0); // bounding box
	if( !bbox )
		return;

	Vector mins, maxs;
	Math::VectorTransform(bbox->bbmin, matrix[bbox->bone], mins);
	Math::VectorTransform(bbox->bbmax, matrix[bbox->bone], maxs);

	Vector center = ( mins + maxs ) * 0.5f;

	// 0 - center, 1 - forehead, 2 - skullcap, 3 - upperleftear, 4 - upperrightear, 5 - uppernose, 6 - upperbackofhead
	// 7 - leftear, 8 - rightear, 9 - nose, 10 - backofhead
	Vector headPoints[11] = { center, center, center, center, center, center, center, center, center, center, center };
	headPoints[1].z += bbox->radius * 0.60f;
	headPoints[2].z += bbox->radius * 1.25f;
	headPoints[3].x += bbox->radius * 0.80f;
	headPoints[3].z += bbox->radius * 0.60f;
	headPoints[4].x -= bbox->radius * 0.80f;
	headPoints[4].z += bbox->radius * 0.90f;
	headPoints[5].y += bbox->radius * 0.80f;
	headPoints[5].z += bbox->radius * 0.90f;
	headPoints[6].y -= bbox->radius * 0.80f;
	headPoints[6].z += bbox->radius * 0.90f;
	headPoints[7].x += bbox->radius * 0.80f;
	headPoints[8].x -= bbox->radius * 0.80f;
	headPoints[9].y += bbox->radius * 0.80f;
	headPoints[10].y -= bbox->radius * 0.80f;


	Autowall::FireBulletData data;
	for ( int i = 0; i < 11; i++ ) {
		int damage = (int)Autowall::GetDamage( headPoints[i], !Settings::Aimbot::friendly, data );
		char buffer[4];
		snprintf(buffer, sizeof(buffer), "%d", damage);

		Vector string2D;
		if( debugOverlay->ScreenPosition( headPoints[i], string2D ) )
			continue;
		Draw::AddText( string2D.x, string2D.y, buffer, ImColor( 255, 0, 255, 255 ) );
	}
}

static void DrawHeaddot( C_BasePlayer* player ) {

	Vector head2D;
	Vector head3D = player->GetBonePosition( BONE_HEAD );
	if ( debugOverlay->ScreenPosition( Vector( head3D.x, head3D.y, head3D.z ), head2D ) )
		return;

	bool bIsVisible = false;
	if ( Settings::ESP::Filters::visibilityCheck || Settings::ESP::Filters::legit )
		bIsVisible = Entity::IsVisible( player, BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck );

	Draw::AddCircleFilled( head2D.x, head2D.y, Settings::ESP::HeadDot::size, ESP::GetESPPlayerColor( player, bIsVisible ), 10 );
}

static void DrawSounds( C_BasePlayer *player, ImColor playerColor ) {
    std::unique_lock<std::mutex> lock( footstepMutex, std::try_to_lock );
    if( lock.owns_lock() ){
        if ( playerFootsteps[player->GetIndex()].empty() )
            return;

        for ( auto it = playerFootsteps[player->GetIndex()].begin(); it != playerFootsteps[player->GetIndex()].end(); it++ ){
            long diff = it->expiration - Util::GetEpochTime();

            if ( diff <= 0 ){
                playerFootsteps[player->GetIndex()].pop_front(); // This works because footsteps are a trail.
                continue;
            }

            float percent = ( float ) diff / ( float ) Settings::ESP::Sounds::time;
            Color drawColor = Color::FromImColor( playerColor );
            drawColor.a = std::min( powf( percent * 2, 0.6f ), 1.f ) * drawColor.a; // fades out alpha when its below 0.5

            float circleRadius = fabs( percent - 1.0f ) * 42.0f;
            float points = std::max(12.0f, circleRadius * 0.75f);

            Draw::AddCircle3D( it->position, circleRadius, ImColor(drawColor.r, drawColor.g, drawColor.b, drawColor.a ), (int)points );
        }
        footstepMutex.unlock();
    }
}

static void DrawPlayerHealthBars( C_BasePlayer* player, int x, int y, int w, int h, ImColor color ) {
	int boxSpacing = Settings::ESP::Boxes::enabled ? 3 : 0;
	ImColor barColor;

	// clamp it to 100
	int healthValue = std::max( 0, std::min( player->GetHealth(), 100 ) );
	float HealthPerc = healthValue / 100.f;

	int barx = x;
	int bary = y;
	int barw = w;
	int barh = h;

	if ( Settings::ESP::Bars::colorType == BarColorType::HEALTH_BASED )
		barColor = ImColor(
				std::min( 510 * ( 100 - healthValue ) / 100, 255 ),
				std::min( 510 * healthValue / 100, 255 ),
				25,
				255
		);
	else if ( Settings::ESP::Bars::colorType == BarColorType::STATIC_COLOR )
		barColor = color ;

	if ( Settings::ESP::Bars::type == BarType::VERTICAL ) {
		barw = 4; // outline(1px) + bar(2px) + outline(1px) = 6px;
		barx -= barw + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 8 px
		Draw::AddRectFilled( barx, bary, barx + barw, bary + barh, ImColor( 10, 10, 10, 255 ) );

		if ( HealthPerc > 0 )
			Draw::AddRectFilled( barx + 1, bary + ( barh * ( 1.f - HealthPerc ) ) + 1,
									 barx + barw - 1, bary + barh - 1, barColor);

		barsSpacing.x += barw;
	} else if ( Settings::ESP::Bars::type == BarType::VERTICAL_RIGHT ) {
		barx += barw + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 8 px
		barw = 4; // outline(1px) + bar(2px) + outline(1px) = 6px;

		Draw::AddRectFilled( barx, bary, barx + barw, bary + barh, ImColor( 10, 10, 10, 255 ) );

		if ( HealthPerc > 0 )
			Draw::AddRectFilled( barx + 1, bary + ( barh * ( 1.f - HealthPerc ) ) + 1, barx + barw - 1,
									 bary + barh - 1, barColor );

		barsSpacing.x += barw;
	} else if ( Settings::ESP::Bars::type == BarType::HORIZONTAL ) {
		bary += barh + boxSpacing; // player box(?px) + spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 5 px
		barh = 4; // outline(1px) + bar(2px) + outline(1px) = 4px;

		Draw::AddRectFilled( barx, bary, barx + barw, bary + barh, ImColor( 10, 10, 10, 255 ) );

		if ( HealthPerc > 0 ) {
			barw *= HealthPerc;
			Draw::AddRect( barx + 1, bary + 1, barx + barw - 1, bary + barh - 1, barColor );
		}
		barsSpacing.y += barh;
	} else if ( Settings::ESP::Bars::type == BarType::HORIZONTAL_UP ) {
		barh = 4; // outline(1px) + bar(2px) + outline(1px) = 4px;
		bary -= barh + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 5 px

		Draw::AddRect( barx - 1, bary - 1, barx + barw + 1, bary + barh + 1, ImColor( 255, 255, 255, 170 ) );
		Draw::AddRectFilled( barx, bary, barx + barw, bary + barh, ImColor( 10, 10, 10, 255 ) );

		if ( HealthPerc > 0 ) {
			barw *= HealthPerc;
			Draw::AddRect( barx + 1, bary + 1, barx + barw - 1, bary + barh - 1, barColor );
		}
		barsSpacing.y += barh;
	}
}

static void DrawPlayerText( C_BasePlayer* player, C_BasePlayer* localplayer, int x, int y, int w, int h ) {
	int boxSpacing = Settings::ESP::Boxes::enabled ? 3 : 0;
	int lineNum = 1;
	int nameOffset = ( int ) ( Settings::ESP::Bars::type == BarType::HORIZONTAL_UP ? boxSpacing + barsSpacing.y : 0 );

	Vector2D textSize = Draw::GetTextSize( XORSTR( "Hi" ), esp_font );
	// draw name
	if ( Settings::ESP::Info::name || Settings::ESP::Info::clan ) {
		std::string displayString;
		IEngineClient::player_info_t playerInfo;
		engine->GetPlayerInfo( player->GetIndex(), &playerInfo );
		if ( Settings::ESP::Info::clan )
			displayString += std::string( ( *csPlayerResource )->GetClan( player->GetIndex() ) );

		if ( Settings::ESP::Info::clan && Settings::ESP::Info::name )
			displayString += " ";

		if ( Settings::ESP::Info::name )
			displayString += playerInfo.name;

		Vector2D nameSize = Draw::GetTextSize( displayString.c_str(), esp_font );
		Draw::AddText( x + ( w / 2 ) - ( nameSize.x / 2 ), ( y - textSize.y - nameOffset ), displayString.c_str(), Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
		lineNum++;
	}

	// draw steamid
	if ( Settings::ESP::Info::steamId ) {
		IEngineClient::player_info_t playerInfo;
		engine->GetPlayerInfo( player->GetIndex(), &playerInfo );
		Vector2D rankSize = Draw::GetTextSize( playerInfo.guid, esp_font );
		Draw::AddText( ( x + ( w / 2 ) - ( rankSize.x / 2 ) ),( y - ( textSize.y * lineNum ) - nameOffset ), playerInfo.guid, Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
		lineNum++;
	}

	// draw rank
	if ( Settings::ESP::Info::rank ) {
		int rank = *( *csPlayerResource )->GetCompetitiveRanking( player->GetIndex() );

		if ( rank >= 0 && rank < 19 ) {
			Vector2D rankSize = Draw::GetTextSize( ESP::ranks[rank], esp_font );
			Draw::AddText( ( x + ( w / 2 ) - ( rankSize.x / 2 ) ), ( y - ( textSize.y * lineNum ) - nameOffset ), ESP::ranks[rank], Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
		}
	}

	// health
	if ( Settings::ESP::Info::health ) {
		std::string buf = std::to_string( player->GetHealth() ) + XORSTR( " HP" );
		Draw::AddText( x + w + boxSpacing, ( y + h - textSize.y ), buf.c_str(), Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
	}

	// armor
	if ( Settings::ESP::Info::armor ) {
		std::string buf = std::to_string( player->GetArmor() ) + (player->HasHelmet() ? XORSTR(" AP*") : XORSTR(" AP"));
		Draw::AddText( x + w + boxSpacing, ( y + h - (textSize.y / 3) ), buf.c_str(), Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
	}

	// weapon
	C_BaseCombatWeapon* activeWeapon = ( C_BaseCombatWeapon* ) entityList->GetClientEntityFromHandle( player->GetActiveWeapon() );
	if ( Settings::ESP::Info::weapon && activeWeapon ) {
		std::string modelName = Util::Items::GetItemDisplayName( *activeWeapon->GetItemDefinitionIndex() );
		int offset = ( int ) ( Settings::ESP::Bars::type == BarType::HORIZONTAL ||
							   Settings::ESP::Bars::type == BarType::INTERWEBZ ? boxSpacing + barsSpacing.y + 1 : 0 );

		Vector2D weaponTextSize = Draw::GetTextSize( modelName.c_str(), esp_font );
		Draw::AddText( ( x + ( w / 2 ) - ( weaponTextSize.x / 2 ) ), y + h + offset, modelName.c_str(), Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
	}
	// draw info
	std::vector<std::string> stringsToShow;

	if (Settings::ESP::Info::money)
	{
		char money[8];
        snprintf(money, 6, "$%d", player->GetMoney());
		stringsToShow.push_back(money);
	}
	if ( Settings::ESP::Info::scoped && player->IsScoped() )
		stringsToShow.push_back( XORSTR( "Scoped" ) );
	if (Settings::ESP::Info::reloading)
	{
		CUtlVector<AnimationLayer> *layers = player->GetAnimOverlay();
		for (int i = 0; i <= layers->Count(); i++)
		{
			if (player->GetSequenceActivity(layers->operator[](i).m_nSequence) == (int)CCSGOAnimStatePoses::ACT_CSGO_RELOAD && layers->operator[](i).m_flWeight != 0.f)
				stringsToShow.push_back( XORSTR( "Reloading" ) );
		}
	}
	if ( Settings::ESP::Info::flashed && player->IsFlashed())
		stringsToShow.push_back( XORSTR( "Flashed" ) );
	if ( Settings::ESP::Info::planting && Entity::IsPlanting( player ) )
		stringsToShow.push_back( XORSTR( "Planting" ) );
	if ( Settings::ESP::Info::planting && player->GetIndex() == ( *csPlayerResource )->GetPlayerC4() )
		stringsToShow.push_back( XORSTR( "Bomb Carrier" ) );
	if ( Settings::ESP::Info::hasDefuser && player->HasDefuser() )
		stringsToShow.push_back( XORSTR( "Kit" ) );
	if ( Settings::ESP::Info::defusing && player->IsDefusing() )
		stringsToShow.push_back( XORSTR( "Defusing" ) );
	if ( Settings::ESP::Info::grabbingHostage && player->IsGrabbingHostage() )
		stringsToShow.push_back( XORSTR( "Hostage Carrier" ) );
	if ( Settings::ESP::Info::rescuing && player->IsRescuing() )
		stringsToShow.push_back( XORSTR( "Rescuing" ) );
	if ( Settings::ESP::Info::location )
		stringsToShow.push_back( player->GetLastPlaceName() );
	if (Settings::Debug::AnimLayers::draw){
		CUtlVector<AnimationLayer> *layers = player->GetAnimOverlay();
		for ( int i = 0; i <= layers->Count(); i++ ){
			stringsToShow.push_back( Util::GetActivityName(player->GetSequenceActivity(layers->operator[](i).m_nSequence)) );
		}
	}


	for( unsigned int i = 0; i < stringsToShow.size(); i++ ){
		Draw::AddText( x + w + boxSpacing, ( y + ( i * ( textSize.y + 2 ) ) ), stringsToShow[i].c_str(), Entity::IsTeamMate(player, localplayer) ? Settings::ESP::allyInfoColor.Color() : Settings::ESP::enemyInfoColor.Color() );
	}
}


static void DrawPlayer(C_BasePlayer* player)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (player == localplayer && !Settings::ESP::Filters::localplayer)
		return;

	if (!Entity::IsTeamMate(player, localplayer) && !Settings::ESP::Filters::enemies)
		return;

	if (player != localplayer && Entity::IsTeamMate(player, localplayer) && !Settings::ESP::Filters::allies)
		return;

	bool bIsVisible = false;
	if (Settings::ESP::Filters::visibilityCheck || Settings::ESP::Filters::legit)
	{
		bIsVisible = Entity::IsVisible(player, BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck);
		if (!bIsVisible && Settings::ESP::Filters::legit)
			return;
	}

	ImColor playerColor = ESP::GetESPPlayerColor(player, bIsVisible);

	int x, y, w, h;
	if (!GetBox(player, x, y, w, h))
		return;

	if (Settings::ESP::Boxes::enabled)
		DrawBox(playerColor, x, y, w, h, player);

	if (Settings::ESP::Sprite::enabled)
        DrawSprite(x, y, w, h, player);

	if (Settings::ESP::Bars::enabled)
		DrawPlayerHealthBars( player, x, y, w, h, playerColor );

	if (Settings::ESP::Skeleton::enabled)
		DrawSkeleton(player, localplayer);

	if (Settings::ESP::BulletTracers::enabled)
		DrawBulletTrace(player);

	if (Settings::ESP::Tracers::enabled && player != localplayer)
		DrawTracer(player);

	if (Settings::ESP::HeadDot::enabled)
		DrawHeaddot(player);

	if (Settings::Debug::AutoWall::debugView)
		DrawAutoWall(player);

	if ( Settings::Debug::BoneMap::draw )
		DrawBoneMap( player );

	if (Settings::Debug::AutoAim::drawTarget)
		DrawAimbotSpot();

    if (Settings::ESP::Sounds::enabled) {
		DrawSounds( player, playerColor );
	}


	/* Checks various Text Settings */
	DrawPlayerText( player, localplayer, x, y, w, h );
}

static void DrawBomb(C_BaseCombatWeapon* bomb, C_BasePlayer* localplayer)
{
	if (!(*csGameRules) || !(*csGameRules)->IsBombDropped())
		return;

	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(bomb, localplayer))
		return;

	DrawEntity(bomb, XORSTR("Bomb"), Settings::ESP::bombColor.Color());
}

static void DrawPlantedBomb(C_PlantedC4* bomb, C_BasePlayer* localplayer)
{
	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(bomb, localplayer))
		return;

	ImColor color = bomb->GetBombDefuser() != -1 || bomb->IsBombDefused() ? Settings::ESP::bombDefusingColor.Color() : Settings::ESP::bombColor.Color();

	float bombTimer = bomb->GetBombTime() - globalVars->curtime;
	std::stringstream displayText;
	if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
	{
		displayText << XORSTR("Bomb");
	}
	else
	{
		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		Vector vecOrigin = bomb->GetVecOrigin();

		float flDistance = localplayer->GetEyePosition().DistTo(vecOrigin);

		float a = 450.7f;
		float b = 75.68f;
		float c = 789.2f;
		float d = ((flDistance - b) / c);
		float flDamage = a * expf(-d * d);

		float damage = std::max((int) ceilf(GetArmourHealth(flDamage, localplayer->GetArmor())), 0);

		displayText << XORSTR("Bomb: ") << std::fixed << std::showpoint << std::setprecision(1) << bombTimer << XORSTR(", damage: ") << (int) damage;
	}

	DrawEntity(bomb, displayText.str().c_str(), color);
}

static void DrawDefuseKit(C_BaseEntity* defuser, C_BasePlayer* localplayer)
{
	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(defuser, localplayer))
		return;
	DrawEntity(defuser, XORSTR("Defuser"), Settings::ESP::defuserColor.Color());
}

static void DrawDroppedWeapons(C_BaseCombatWeapon* weapon, C_BasePlayer* localplayer)
{
	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(weapon, localplayer))
		return;

	Vector vOrig = weapon->GetVecOrigin();
	int owner = weapon->GetOwner();

	if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
		return;

	std::string modelName = Util::Items::GetItemDisplayName(*weapon->GetItemDefinitionIndex());

	if (weapon->GetAmmo() > 0)
	{
		modelName += XORSTR(" | ");
		modelName += std::to_string(weapon->GetAmmo());
	}

	DrawEntity(weapon, modelName.c_str(), Settings::ESP::weaponColor.Color());
}

static void DrawHostage(C_BaseEntity* hostage, C_BasePlayer* localplayer)
{
	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(hostage, localplayer))
		return;

	DrawEntity(hostage, XORSTR("Hostage"), Settings::ESP::hostageColor.Color());
}

static void DrawChicken(C_BaseEntity* chicken)
{
	DrawEntity(chicken, XORSTR("Chicken"), Settings::ESP::chickenColor.Color());
}

static void DrawFish(C_BaseEntity* fish)
{
	DrawEntity(fish, XORSTR("Fish"), Settings::ESP::fishColor.Color());
}

static void DrawSafe(C_BaseEntity* safe, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(safe, localplayer))
		return;
	if (*(bool*)((uintptr_t)safe + offsets.DT_BRC4Target.m_bBrokenOpen))
		return;
    DrawEntity(safe, XORSTR("Safe"), Settings::ESP::DangerZone::safeColor.Color());
}

static void DrawAmmoBox(C_BaseEntity *ammobox, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(ammobox, localplayer))
		return;
    DrawEntity(ammobox, XORSTR("Ammo box"), Settings::ESP::DangerZone::ammoboxColor.Color());
}

static void DrawSentryTurret(C_BaseEntity *sentry, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(sentry, localplayer))
		return;

	std::string name = XORSTR("Sentry Turret");
	name += XORSTR(" | ");
	name += std::to_string(*(int*)((uintptr_t)sentry + offsets.DT_Dronegun.m_iHealth));
	name += XORSTR(" HP");
    DrawEntity(sentry, name.c_str(), Settings::ESP::DangerZone::dronegunColor.Color());
}

static void DrawRadarJammer(C_BaseEntity *jammer, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(jammer, localplayer))
		return;
    DrawEntity(jammer, XORSTR("Radar Jammer"), Settings::ESP::DangerZone::radarjammerColor.Color());
}

static void DrawExplosiveBarrel(C_BaseEntity *barrel, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(barrel, localplayer))
		return;
	studiohdr_t* barrelModel = modelInfo->GetStudioModel(barrel->GetModel());
	if (!barrelModel)
		return;
	std::string mdlName = barrelModel->name;
	mdlName = mdlName.substr(mdlName.find_last_of('/') + 1);
	if (mdlName.find(XORSTR("exploding_barrel.mdl")) == mdlName.npos)
		return;
    DrawEntity(barrel, XORSTR("Explosive Barrel"), Settings::ESP::DangerZone::barrelColor.Color());
}

static void DrawDrone(C_BaseEntity *drone, C_BasePlayer* localplayer)
{
	// TODO: Add Drone info (owner/package).
	if (!dzShouldDraw(drone, localplayer))
		return;
    DrawEntity(drone, XORSTR("Drone"), Settings::ESP::DangerZone::droneColor.Color());
}

static void DrawCash(C_BaseEntity *cash, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(cash, localplayer))
		return;
    DrawEntity(cash, XORSTR("Cash"), Settings::ESP::DangerZone::cashColor.Color());
}

static void DrawTablet(C_BaseEntity *tablet, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(tablet, localplayer))
		return;
    DrawEntity(tablet, XORSTR("Tablet"), Settings::ESP::DangerZone::tabletColor.Color());
}

static void DrawHealthshot(C_BaseEntity *healthshot, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(healthshot, localplayer))
		return;
    DrawEntity(healthshot, XORSTR("Healthshot"), Settings::ESP::DangerZone::healthshotColor.Color());
}

static void DrawLootCrate(C_BaseEntity *crate, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(crate, localplayer))
		return;
    studiohdr_t* crateModel = modelInfo->GetStudioModel(crate->GetModel());
    if (!crateModel)
        return;
    std::string mdlName = crateModel->name;
    mdlName = mdlName.substr(mdlName.find_last_of('/') + 1);
    std::string crateName;
    if (mdlName.find(XORSTR("case_pistol")) != mdlName.npos)
        crateName = XORSTR("Pistol Case");
    else if (mdlName.find(XORSTR("light_weapon")) != mdlName.npos)
        crateName = XORSTR("SMG Case");
    else if (mdlName.find(XORSTR("heavy_weapon")) != mdlName.npos)
        crateName = XORSTR("Heavy Case");
    else if (mdlName.find(XORSTR("explosive")) != mdlName.npos)
        crateName = XORSTR("Explosive Case");
    else if (mdlName.find(XORSTR("tools")) != mdlName.npos)
        crateName = XORSTR("Tools Case");
    else if (mdlName.find(XORSTR("dufflebag")) != mdlName.npos)
        crateName = XORSTR("Duffle Bag");
	else if (mdlName.find(XORSTR("random")) != mdlName.npos)
        crateName = XORSTR("Airdrop");

		crateName += XORSTR(" | ");
		crateName += std::to_string(*(int*)((uintptr_t)crate + offsets.DT_PhysPropLootCrate.m_iHealth));
		crateName += XORSTR(" HP");

    DrawEntity(crate, crateName.c_str(), Settings::ESP::DangerZone::lootcrateColor.Color());
}

static void DrawMelee(C_BaseCombatWeapon *weapon, C_BasePlayer* localplayer)
{
	if (!weapon)
		return;

	if (!dzShouldDraw(weapon, localplayer))
		return;

    std::string modelName = Util::Items::GetItemDisplayName(*weapon->GetItemDefinitionIndex());
    DrawEntity(weapon, modelName.c_str(), Settings::ESP::DangerZone::meleeColor.Color());
}

static void DrawDZItems(C_BaseEntity *item, C_BasePlayer* localplayer)
{
	if (!dzShouldDraw(item, localplayer))
		return;

    studiohdr_t* itemModel = modelInfo->GetStudioModel(item->GetModel());

    if (!itemModel)
        return;

    std::string mdlName = itemModel->name;
    mdlName = mdlName.substr(mdlName.find_last_of('/') + 1);
    std::string itemName;

	if (mdlName.find(XORSTR("dz_armor_helmet")) != mdlName.npos) // upgrade_...
		itemName = XORSTR("Full Armor");
	else if (mdlName.find(XORSTR("dz_armor")) != mdlName.npos)
		itemName = XORSTR("Armor");
	else if (mdlName.find(XORSTR("dz_helmet")) != mdlName.npos)
		itemName = XORSTR("Helmet");
	else if (mdlName.find(XORSTR("upgrade_tablet_drone")) != mdlName.npos)
		itemName = XORSTR("Tablet (drone)");
	else if (mdlName.find(XORSTR("upgrade_tablet_zone")) != mdlName.npos)
		itemName = XORSTR("Tablet (zone)");
	else if (mdlName.find(XORSTR("upgrade_tablet_hires")) != mdlName.npos)
		itemName = XORSTR("Tablet (highres)");
	else if (mdlName.find(XORSTR("briefcase")) != mdlName.npos)
		itemName = XORSTR("Briefcase");
	else if (mdlName.find(XORSTR("parachutepack")) != mdlName.npos)
		itemName = XORSTR("Parachute");
	else if (mdlName.find(XORSTR("exojump")) != mdlName.npos) // TODO: not working.
		itemName = XORSTR("Exojump");
	else
		itemName = mdlName;

    DrawEntity(item, itemName.c_str(), Settings::ESP::DangerZone::upgradeColor.Color());
}

static void DrawThrowable(C_BaseEntity* throwable, ClientClass* client, C_BasePlayer* localplayer)
{
	// Draw Distance only in DangerZone
	if (Util::IsDangerZone() && !dzShouldDraw(throwable, localplayer))
		return;

	model_t* nadeModel = throwable->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = modelInfo->GetStudioModel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, XORSTR("thrown")) && !strstr(hdr->name, XORSTR("dropped")))
		return;

	ImColor nadeColor = ImColor(255, 255, 255, 255);
	std::string nadeName = XORSTR("Unknown Grenade");

	IMaterial* mats[32];
	modelInfo->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), XORSTR("flashbang")))
		{
			nadeName = XORSTR("Flashbang");
			nadeColor = Settings::ESP::flashbangColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("m67_grenade")) || strstr(mat->GetName(), XORSTR("hegrenade")))
		{
			nadeName = XORSTR("HE Grenade");
			nadeColor = Settings::ESP::grenadeColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("smoke")))
		{
			nadeName = XORSTR("Smoke");
			nadeColor = Settings::ESP::smokeColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("decoy")))
		{
			nadeName = XORSTR("Decoy");
			nadeColor = Settings::ESP::decoyColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("incendiary")) || strstr(mat->GetName(), XORSTR("molotov")))
		{
			nadeName = XORSTR("Molotov");
			nadeColor = Settings::ESP::molotovColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("bump_mine")))
		{
			nadeName = XORSTR("Bump Mine (placed)");
			nadeColor = Settings::ESP::mineColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), XORSTR("c4"))) // breach charge
		{
			nadeName = XORSTR("Breach Charge (placed)");
			nadeColor = Settings::ESP::chargeColor.Color();
			break;
		}
	}

	DrawEntity(throwable, nadeName.c_str(), nadeColor);
}

static void DrawGlow()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 0; i < glowManager->m_GlowObjectDefinitions.Count(); i++)
	{
		GlowObjectDefinition_t& glow_object = glowManager->m_GlowObjectDefinitions[i];

		if (glow_object.IsUnused() || !glow_object.m_pEntity)
			continue;

		ImColor color;
		ClientClass* client = glow_object.m_pEntity->GetClientClass();
		bool shouldGlow = true;

		if (client->m_ClassID == EClassIds::CCSPlayer)
		{
			C_BasePlayer* player = (C_BasePlayer*) glow_object.m_pEntity;

			if (player->GetDormant() || !player->GetAlive())
				continue;

			if (player == localplayer)
			{
				color = Settings::ESP::Glow::localplayerColor.Color(player);
			}
			else
			{
				if (!Entity::IsTeamMate(player, localplayer))
				{
					if (Entity::IsVisible(player, BONE_HEAD))
						color = Settings::ESP::Glow::enemyVisibleColor.Color(player);
					else
						color = Settings::ESP::Glow::enemyColor.Color(player);
				}
				else
					color = Settings::ESP::Glow::allyColor.Color(player);
			}
		}
		else if (client->m_ClassID != EClassIds::CBaseWeaponWorldModel &&
				 (strstr(client->m_pNetworkName, XORSTR("Weapon")) || client->m_ClassID == EClassIds::CDEagle || client->m_ClassID == EClassIds::CAK47))
		{
			color = Settings::ESP::Glow::weaponColor.Color();
		}
		else if (client->m_ClassID == EClassIds::CBaseCSGrenadeProjectile || client->m_ClassID == EClassIds::CDecoyProjectile ||
				 client->m_ClassID == EClassIds::CMolotovProjectile || client->m_ClassID == EClassIds::CSmokeGrenadeProjectile)
		{
			color = Settings::ESP::Glow::grenadeColor.Color();
		}
		else if (client->m_ClassID == EClassIds::CBaseAnimating)
		{
			color = Settings::ESP::Glow::defuserColor.Color();

			if (localplayer->HasDefuser() || localplayer->GetTeam() == TeamID::TEAM_TERRORIST)
				shouldGlow = false;
		}
		else if (client->m_ClassID == EClassIds::CChicken)
		{
			color = Settings::ESP::Glow::chickenColor.Color();

			*reinterpret_cast<C_Chicken*>(glow_object.m_pEntity)->GetShouldGlow() = shouldGlow;
		}

		shouldGlow = shouldGlow && color.Value.w > 0;

		glow_object.m_flGlowColor[0] = color.Value.x;
		glow_object.m_flGlowColor[1] = color.Value.y;
		glow_object.m_flGlowColor[2] = color.Value.z;
		glow_object.m_flGlowAlpha = shouldGlow ? color.Value.w : 1.0f;
		glow_object.m_flBloomAmount = 1.0f;
		glow_object.m_bRenderWhenOccluded = shouldGlow;
		glow_object.m_bRenderWhenUnoccluded = false;
	}
}

static void DrawFOVCrosshair()
{
	if (!Settings::ESP::FOVCrosshair::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer->GetAlive())
		return;

	if (Settings::Aimbot::AutoAim::fov > OverrideView::currentFOV)
		return;

	float radius;
	if (Settings::Aimbot::AutoAim::realDistance)
	{
		Vector src3D, dst3D, forward;
		trace_t tr;
		Ray_t ray;
		CTraceFilter filter;

		QAngle angles = viewanglesBackup;
		Math::AngleVectors(angles, forward);
		filter.pSkip = localplayer;
		src3D = localplayer->GetEyePosition();
		dst3D = src3D + (forward * 8192);

		ray.Init(src3D, dst3D);
		trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

		QAngle leftViewAngles = QAngle(angles.x, angles.y - 90.f, 0.f);
		Math::NormalizeAngles(leftViewAngles);
		Math::AngleVectors(leftViewAngles, forward);
		forward *= Settings::Aimbot::AutoAim::fov * 5.f;

		Vector maxAimAt = tr.endpos + forward;

		Vector max2D;
		if (debugOverlay->ScreenPosition(maxAimAt, max2D))
			return;

		radius = fabsf(Paint::engineWidth / 2 - max2D.x);
	}
	else
		radius = ((Settings::Aimbot::AutoAim::fov / OverrideView::currentFOV) * Paint::engineWidth) / 2;

	radius = std::min(radius, (((180.f / OverrideView::currentFOV) * Paint::engineWidth) / 2)); // prevents a big radius (CTD).

	if (Settings::ESP::FOVCrosshair::filled)
		Draw::AddCircleFilled(Paint::engineWidth / 2, Paint::engineHeight / 2 , radius, Settings::ESP::FOVCrosshair::color.Color(), std::max(12, (int)radius*2));
	else
		Draw::AddCircle(Paint::engineWidth / 2, Paint::engineHeight / 2, radius, Settings::ESP::FOVCrosshair::color.Color(), std::max(12, (int)radius*2));
}

static void DrawSpread()
{
    if ( !Settings::ESP::Spread::enabled && !Settings::ESP::Spread::spreadLimit )
        return;

    C_BasePlayer* localplayer = ( C_BasePlayer* ) entityList->GetClientEntity( engine->GetLocalPlayer() );
    if ( !localplayer )
        return;

    C_BaseCombatWeapon* activeWeapon = ( C_BaseCombatWeapon* ) entityList->GetClientEntityFromHandle(
            localplayer->GetActiveWeapon() );
    if ( !activeWeapon )
        return;

    if ( Settings::ESP::Spread::enabled ) {
        float cone = activeWeapon->GetSpread() + activeWeapon->GetInaccuracy();
        if ( cone > 0.0f ) {
            float radius = ( cone * Paint::engineHeight ) / 1.5f;
            Draw::AddRect( ( ( Paint::engineWidth / 2 ) - radius ), ( Paint::engineHeight / 2 ) - radius + 1,
                               ( Paint::engineWidth / 2 ) + radius + 1, ( Paint::engineHeight / 2 ) + radius + 2,
                               Settings::ESP::Spread::color.Color() );
        }
    }
    if ( Settings::ESP::Spread::spreadLimit ) {
        float cone = Settings::Aimbot::SpreadLimit::value;
        if ( cone > 0.0f ) {
            float radius = ( cone * Paint::engineHeight ) / 1.5f;
            Draw::AddRect( ( ( Paint::engineWidth / 2 ) - radius ), ( Paint::engineHeight / 2 ) - radius + 1,
                               ( Paint::engineWidth / 2 ) + radius + 1, ( Paint::engineHeight / 2 ) + radius + 2 ,
                               Settings::ESP::Spread::spreadLimitColor.Color() );
        }
    }
}

static void DrawScope()
{
    C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
    if (!localplayer)
        return;

    C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
    if (!activeWeapon)
        return;

    if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_SG556 || *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_AUG)
        return;

    Draw::AddLine(0, Paint::engineHeight * 0.5, Paint::engineWidth, Paint::engineHeight * 0.5, ImColor(0, 0, 0, 255));
    Draw::AddLine(Paint::engineWidth * 0.5, 0, Paint::engineWidth * 0.5, Paint::engineHeight, ImColor(0, 0, 0, 255));
}

bool ESP::PrePaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (Settings::ESP::enabled && Settings::NoScopeBorder::enabled && strcmp("HudZoom", panel->GetName(vgui_panel)) == 0)
		return false;

	return true;
}
void ESP::Paint()
{
	if (!Settings::ESP::enabled && !inputSystem->IsButtonDown(Settings::ESP::key))
		return;

	if (!engine->IsInGame())
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	for (int i = 1; i < entityList->GetHighestEntityIndex(); i++)
	{
		C_BaseEntity* entity = entityList->GetClientEntity(i);
		if (!entity)
			continue;

		ClientClass* client = entity->GetClientClass();

		if (client->m_ClassID == EClassIds::CCSPlayer && (Settings::ESP::Filters::enemies || Settings::ESP::Filters::allies || (Settings::ESP::Filters::localplayer && Settings::ThirdPerson::enabled)))
		{
			C_BasePlayer* player = (C_BasePlayer*) entity;

			if (player->GetDormant() || !player->GetAlive())
				continue;

			DrawPlayer(player);
		}
		if ((client->m_ClassID != EClassIds::CBaseWeaponWorldModel && (strstr(client->m_pNetworkName, XORSTR("Weapon")) || client->m_ClassID == EClassIds::CDEagle || client->m_ClassID == EClassIds::CAK47 || client->m_ClassID == EClassIds::CBreachCharge || client->m_ClassID == EClassIds::CBumpMine)) && client->m_ClassID != EClassIds::CPhysPropWeaponUpgrade && Settings::ESP::Filters::weapons)
		{
			DrawDroppedWeapons((C_BaseCombatWeapon*) entity, localplayer);
		}
		else if (client->m_ClassID == EClassIds::CC4 && Settings::ESP::Filters::bomb)
		{
			DrawBomb((C_BaseCombatWeapon*) entity, localplayer);
		}
		else if (client->m_ClassID == EClassIds::CPlantedC4 && Settings::ESP::Filters::bomb)
		{
			DrawPlantedBomb((C_PlantedC4*) entity, localplayer);
		}
		else if (client->m_ClassID == EClassIds::CHostage && Settings::ESP::Filters::hostages)
		{
			DrawHostage(entity, localplayer);
		}
		else if (client->m_ClassID == EClassIds::CBaseAnimating && Settings::ESP::Filters::defusers)
		{
			DrawDefuseKit(entity, localplayer);
		}
		else if (client->m_ClassID == EClassIds::CChicken && Settings::ESP::Filters::chickens)
		{
			DrawChicken(entity);
		}
		else if (client->m_ClassID == EClassIds::CFish && Settings::ESP::Filters::fishes)
		{
			DrawFish(entity);
		}
		else if (Settings::ESP::Filters::throwables && strstr(client->m_pNetworkName, XORSTR("Projectile")))
		{
			DrawThrowable(entity, client, localplayer);
		}
		else if (Util::IsDangerZone())
		{
			if (Settings::ESP::DangerZone::safe && client->m_ClassID == EClassIds::CBRC4Target)
				DrawSafe(entity, localplayer);

			else if (Settings::ESP::DangerZone::dronegun && client->m_ClassID == EClassIds::CDronegun)
				DrawSentryTurret(entity, localplayer);

			else if (Settings::ESP::DangerZone::ammobox && client->m_ClassID == EClassIds::CPhysPropAmmoBox)
				DrawAmmoBox(entity, localplayer);

			else if (Settings::ESP::DangerZone::radarjammer && client->m_ClassID == EClassIds::CPhysPropRadarJammer)
				DrawRadarJammer(entity, localplayer);

			else if (Settings::ESP::DangerZone::barrel && client->m_ClassID == EClassIds::CPhysicsProp)
				DrawExplosiveBarrel(entity, localplayer);

			else if (Settings::ESP::DangerZone::drone && client->m_ClassID == EClassIds::CDrone)
				DrawDrone(entity, localplayer);

			else if (Settings::ESP::DangerZone::cash && client->m_ClassID == EClassIds::CItemCash)
				DrawCash(entity, localplayer);

			else if (Settings::ESP::DangerZone::tablet && client->m_ClassID == EClassIds::CTablet)
				DrawTablet(entity, localplayer);

			else if (Settings::ESP::DangerZone::healthshot && client->m_ClassID == EClassIds::CItem_Healthshot)
				DrawHealthshot(entity, localplayer);

			else if (Settings::ESP::DangerZone::lootcrate && client->m_ClassID == EClassIds::CPhysPropLootCrate)
				DrawLootCrate(entity, localplayer);

			else if (Settings::ESP::DangerZone::melee && (client->m_ClassID == EClassIds::CMelee || client->m_ClassID == EClassIds::CKnife))
			{
				C_BaseCombatWeapon* weapon = (C_BaseCombatWeapon*) entity;
				DrawMelee(weapon, localplayer);
			}

			else if (Settings::ESP::DangerZone::upgrade && client->m_ClassID == EClassIds::CPhysPropWeaponUpgrade)
				DrawDZItems(entity, localplayer);
		}
	}

	if (Settings::ESP::FOVCrosshair::enabled)
		DrawFOVCrosshair();
	if (Settings::ESP::Spread::enabled || Settings::ESP::Spread::spreadLimit)
		DrawSpread();
	if (Settings::NoScopeBorder::enabled && localplayer->IsScoped())
		DrawScope();
}

void ESP::DrawModelExecute()
{
	if (!Settings::ESP::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (Settings::ESP::Glow::enabled)
		DrawGlow();
}

void ESP::CreateMove(CUserCmd* cmd)
{
	viewanglesBackup = cmd->viewangles;

    if( Settings::ESP::enabled && Settings::ESP::Sounds::enabled && (Settings::ESP::Filters::allies || Settings::ESP::Filters::enemies || Settings::ESP::Filters::localplayer) ){
        CheckActiveSounds();
    }
}

void ESP::PaintToUpdateMatrix( ) {
	if( !engine->IsInGame() )
		return;

	vMatrix = engine->WorldToScreenMatrix();
}
