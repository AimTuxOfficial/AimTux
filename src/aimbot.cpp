#include "aimbot.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
bool Settings::Aimbot::AimLock::enabled = true;
bool Settings::Aimbot::RCS::enabled = true;

double hyp;

void CalculateAngle (Vector& src, Vector& dst, QAngle& angles)
{
	// Angle deltas
	double delta[3] = { (src[0]-dst[0]), (src[1]-dst[1]), (src[2]-dst[2]) };

	// Hypotenuse
	hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	angles[0] = (float) (atan(delta[2]/hyp) * 57.295779513082f);
	angles[1] = (float) (atan(delta[1]/delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;	// <=== NEVER EVER  EVER EVER EVER CHANGE THIS VALUE
						//					... unless you teh VAC ban ...

	if (delta[0] >= 0.0) angles[1] += 180.0f;

	// Safeguards
	if (angles[1] > 180) angles[1] -= 360;
	if (angles[1] < -180) angles[1] += 360;
	if (angles[0] > 89) angles[0] = 89;
	if (angles[0] < -89) angles[0] = -89;
}


C_BaseEntity* GetClosestEnemy ()
{
	C_BasePlayer* localPlayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseEntity* closestEntity = NULL;
	float dist = 10000000.0f;

	if (!localPlayer)
		return NULL;

	for (int i = 0; i < 64; ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		if (!entity || entity == (C_BaseEntity*)localPlayer ||
				entity->GetDormant() || entity->GetLifeState() != LIFE_ALIVE || entity->GetHealth() <= 0)
			continue;

		C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

		if
		(
			   !entity
			|| entity == (C_BaseEntity*)localPlayer
			|| entity->GetDormant()
			|| entity->GetLifeState() != 0
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localPlayer->GetTeam()
		)
			continue;

		float e_dist = localplayer->GetVecOrigin().DistToSqr (entity->GetVecOrigin());

		if (e_dist < dist)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}

static QAngle vecOldPunchAngle = QAngle();

void Aimbot::RCS (QAngle& angle)
{
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	
	QAngle punchangle = localplayer->GetViewPunch () * 1.98f;
	
	angle -= (punchangle - vecOldPunchAngle);
	
	vecOldPunchAngle = punchangle;
}

void Aimbot::Calculate ()
{
	QAngle angle;
	engine->GetViewAngles (angle);
	
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	
	
	if (Settings::Aimbot::AimLock::enabled)
	{
		C_BaseEntity* entity = GetClosestEnemy ();
		
		
		if (entity != NULL)
		{
			Vector e_vecHead = GetBone (entity, 6);
			Vector p_vecHead = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();
			
			CalculateAngle (p_vecHead, e_vecHead, angle);
		}
	}
	
	if (Settings::Aimbot::RCS::enabled)
		RCS (angle);
	
	engine->SetViewAngles (angle);
}




