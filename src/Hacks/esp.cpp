#include <iomanip>

#include "esp.h"
#include "../Utils/skins.h"

bool Settings::ESP::enabled = false;
TeamColorType Settings::ESP::teamColorType = TeamColorType::RELATIVE;
HealthColorVar Settings::ESP::enemyColor = ImColor(240, 60, 60, 255);
HealthColorVar Settings::ESP::enemyVisibleColor = ImColor(240, 185, 60, 255);
HealthColorVar Settings::ESP::allyColor = ImColor(60, 60, 240, 255);
HealthColorVar Settings::ESP::allyVisibleColor = ImColor(60, 185, 240, 255);
HealthColorVar Settings::ESP::tColor = ImColor(240, 60, 60, 255);
HealthColorVar Settings::ESP::tVisibleColor = ImColor(240, 185, 60, 255);
HealthColorVar Settings::ESP::ctColor = ImColor(60, 60, 240, 255);
HealthColorVar Settings::ESP::ctVisibleColor = ImColor(60, 185, 240, 255);
HealthColorVar Settings::ESP::localplayerColor = ImColor(117, 43, 73, 255);
ColorVar Settings::ESP::bombColor = ImColor(242, 48, 193, 255);
ColorVar Settings::ESP::bombDefusingColor = ImColor(100, 48, 242, 255);
ColorVar Settings::ESP::hostageColor = ImColor(242, 48, 193, 255);
ColorVar Settings::ESP::defuserColor = ImColor(132, 48, 242, 255);
ColorVar Settings::ESP::weaponColor = ImColor(255, 255, 255, 255);
ColorVar Settings::ESP::chickenColor = ImColor(255, 255, 255, 255);
ColorVar Settings::ESP::fishColor = ImColor(255, 255, 255, 255);
ColorVar Settings::ESP::smokeColor = ImColor(32, 224, 22, 255);
ColorVar Settings::ESP::decoyColor = ImColor(32, 224, 22, 255);
ColorVar Settings::ESP::flashbangColor = ImColor(224, 207, 22, 255);
ColorVar Settings::ESP::grenadeColor = ImColor(224, 22, 22, 255);
ColorVar Settings::ESP::molotovColor = ImColor(224, 22, 22, 255);
ColorVar Settings::ESP::Skeleton::color = ImColor(255, 255, 255, 255);
bool Settings::ESP::Glow::enabled = false;
HealthColorVar Settings::ESP::Glow::allyColor = ImColor(0, 50, 200, 200);
HealthColorVar Settings::ESP::Glow::enemyColor = ImColor(200, 0, 50, 200);
HealthColorVar Settings::ESP::Glow::enemyVisibleColor = ImColor(200, 200, 50, 200);
HealthColorVar Settings::ESP::Glow::localplayerColor = ImColor(117, 43, 73, 200);
ColorVar Settings::ESP::Glow::weaponColor = ImColor(200, 0, 50, 200);
ColorVar Settings::ESP::Glow::grenadeColor = ImColor(200, 0, 50, 200);
ColorVar Settings::ESP::Glow::defuserColor = ImColor(100, 100, 200, 200);
ColorVar Settings::ESP::Glow::chickenColor = ImColor(100, 200, 100, 200);
bool Settings::ESP::Filters::legit = false;
bool Settings::ESP::Filters::visibilityCheck = false;
bool Settings::ESP::Filters::smokeCheck = false;
bool Settings::ESP::Filters::enemies = false;
bool Settings::ESP::Filters::allies = false;
bool Settings::ESP::Filters::bomb = false;
bool Settings::ESP::Filters::hostages = false;
bool Settings::ESP::Filters::defusers = false;
bool Settings::ESP::Filters::weapons = false;
bool Settings::ESP::Filters::chickens = false;
bool Settings::ESP::Filters::fishes = false;
bool Settings::ESP::Filters::throwables = false;
bool Settings::ESP::Filters::localplayer = false;
bool Settings::ESP::Info::name = false;
bool Settings::ESP::Info::clan = false;
bool Settings::ESP::Info::steamId = false;
bool Settings::ESP::Info::rank = false;
bool Settings::ESP::Info::health = false;
bool Settings::ESP::Info::weapon = false;
bool Settings::ESP::Info::scoped = false;
bool Settings::ESP::Info::reloading = false;
bool Settings::ESP::Info::flashed = false;
bool Settings::ESP::Info::planting = false;
bool Settings::ESP::Info::hasDefuser = false;
bool Settings::ESP::Info::defusing = false;
bool Settings::ESP::Info::grabbingHostage = false;
bool Settings::ESP::Info::rescuing = false;
bool Settings::ESP::Info::location = false;
bool Settings::ESP::Boxes::enabled = false;
BoxType Settings::ESP::Boxes::type = BoxType::FRAME_2D;
bool Settings::ESP::Bars::enabled = false;
BarColorType Settings::ESP::Bars::colorType = BarColorType::HEALTH_BASED;
BarType Settings::ESP::Bars::type = BarType::HORIZONTAL;
bool Settings::ESP::Tracers::enabled = false;
TracerType Settings::ESP::Tracers::type = TracerType::BOTTOM;
bool Settings::ESP::BulletTracers::enabled = false;
bool Settings::ESP::FOVCrosshair::enabled = false;
bool Settings::ESP::FOVCrosshair::filled = false;
ColorVar Settings::ESP::FOVCrosshair::color = ImColor(180, 50, 50, 255);
bool Settings::ESP::Skeleton::enabled = false;
bool Settings::ESP::Sounds::enabled = false;
int Settings::ESP::Sounds::time = 1000;
bool Settings::NoScopeBorder::enabled = false;
bool Settings::ESP::HeadDot::enabled = false;
float Settings::ESP::HeadDot::size = 2.f;

struct Footstep
{
	long expiration;
	int entityId;
	Vector position;
};

QAngle viewanglesBackup;
std::vector<Footstep> footsteps;

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

// credits to Casual_Hacker from UC for this method (I modified it a lil bit)
float GetArmourHealth(float flDamage, int ArmorValue)
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

bool ESP::GetBox(C_BaseEntity* entity, int& x, int& y, int& w, int& h)
{
	// Variables
	Vector vOrigin, min, max, flb, brt, blb, frt, frb, brb, blt, flt;
	float left, top, right, bottom;

	// Get the locations
	vOrigin = entity->GetVecOrigin();
	min = entity->GetCollideable()->OBBMins() + vOrigin;
	max = entity->GetCollideable()->OBBMaxs() + vOrigin;

	// Points of a 3d bounding box
	Vector points[] = { Vector(min.x, min.y, min.z),
						Vector(min.x, max.y, min.z),
						Vector(max.x, max.y, min.z),
						Vector(max.x, min.y, min.z),
						Vector(max.x, max.y, max.z),
						Vector(min.x, max.y, max.z),
						Vector(min.x, min.y, max.z),
						Vector(max.x, min.y, max.z) };

	// Get screen positions
	if (debugOverlay->ScreenPosition(points[3], flb) || debugOverlay->ScreenPosition(points[5], brt)
		|| debugOverlay->ScreenPosition(points[0], blb) || debugOverlay->ScreenPosition(points[4], frt)
		|| debugOverlay->ScreenPosition(points[2], frb) || debugOverlay->ScreenPosition(points[1], brb)
		|| debugOverlay->ScreenPosition(points[6], blt) || debugOverlay->ScreenPosition(points[7], flt))
		return false;

	// Put them in an array (maybe start them off in one later for speed?)
	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	// Init this shit
	left = flb.x;
	top = flb.y;
	right = flb.x;
	bottom = flb.y;

	// Find the bounding corners for our box
	for (int i = 1; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
	}

	// Width / height
	x = (int) left;
	y = (int) top;
	w = (int) (right - left);
	h = (int) (bottom - top);

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
			if (player->GetTeam() != localplayer->GetTeam())
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

void ESP::DrawBox(Color color, int x, int y, int w, int h, C_BaseEntity* entity)
{
	if (Settings::ESP::Boxes::type == BoxType::FRAME_2D)
	{
		int VertLine = (int) (w * 0.33f);
		int HorzLine = (int) (h * 0.33f);
		int squareLine = std::min(VertLine, HorzLine);

		// top-left corner / color
		Draw::Rectangle(x, y, x + squareLine, y + 1, color);
		Draw::Rectangle(x, y, x + 1, y + squareLine, color);

		// top-left corner / outer outline
		Draw::Rectangle(x - 1, y - 1, x + squareLine, y, Color(10, 10, 10, 190));
		Draw::Rectangle(x - 1, y, x, y + squareLine, Color(10, 10, 10, 190));

		// top-left corner / inner outline
		Draw::Rectangle(x + 1, y + 1, x + squareLine, y + 2, Color(10, 10, 10, 190));
		Draw::Rectangle(x + 1, y + 2, x + 2, y + squareLine, Color(10, 10, 10, 190));

		// top-left corner / missing edges
		Draw::Rectangle(x + squareLine, y - 1, x + squareLine + 1, y + 2, Color(10, 10, 10, 190));
		Draw::Rectangle(x - 1, y + squareLine, x + 2, y + squareLine + 1, Color(10, 10, 10, 190));


		// top-right corner / color
		Draw::Rectangle(x + w - squareLine, y, x + w, y + 1, color);
		Draw::Rectangle(x + w - 1, y, x + w, y + squareLine, color);

		// top-right corner / outer outline
		Draw::Rectangle(x + w - squareLine, y - 1, x + w + 1, y, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w, y, x + w + 1, y + squareLine, Color(10, 10, 10, 190));

		// top-right corner / inner outline
		Draw::Rectangle(x + w - squareLine, y + 1, x + w - 1, y + 2, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w - 2, y + 2, x + w - 1, y + squareLine, Color(10, 10, 10, 190));

		// top-right corner / missing edges
		Draw::Rectangle(x + w - squareLine - 1, y - 1, x + w - squareLine, y + 2, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w - 2, y + squareLine, x + w + 1, y + squareLine + 1, Color(10, 10, 10, 190));


		// bottom-left corner / color
		Draw::Rectangle(x, y + h - 1, x + squareLine, y + h, color);
		Draw::Rectangle(x, y + h - squareLine, x + 1, y + h, color);

		// bottom-left corner / outer outline
		Draw::Rectangle(x - 1, y + h, x + squareLine, y + h + 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x - 1, y + h - squareLine, x, y + h, Color(10, 10, 10, 190));

		// bottom-left corner / inner outline
		Draw::Rectangle(x + 1, y + h - 2, x + squareLine, y + h - 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x + 1, y + h - squareLine, x + 2, y + h - 2, Color(10, 10, 10, 190));

		// bottom-left corner / missing edges
		Draw::Rectangle(x + squareLine, y + h - 2, x + squareLine + 1, y + h + 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x - 1, y + h - squareLine - 1, x + 2, y + h - squareLine, Color(10, 10, 10, 190));


		// bottom-right corner / color
		Draw::Rectangle(x + w - squareLine, y + h - 1, x + w, y + h, color);
		Draw::Rectangle(x + w - 1, y + h - squareLine, x + w, y + h, color);

		// bottom-right corner / outer outline
		Draw::Rectangle(x + w - squareLine, y + h, x + w + 1, y + h + 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w, y + h - squareLine, x + w + 1, y + h + 1, Color(10, 10, 10, 190));

		// bottom-right corner / inner outline
		Draw::Rectangle(x + w - squareLine, y + h - 2, x + w - 1, y + h - 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w - 2, y + h - squareLine, x + w - 1, y + h - 2, Color(10, 10, 10, 190));

		// bottom-right corner / missing edges
		Draw::Rectangle(x + w - squareLine, y + h - 2, x + w - squareLine + 1, y + h + 1, Color(10, 10, 10, 190));
		Draw::Rectangle(x + w - 2, y + h - squareLine - 1, x + w + 1, y + h - squareLine, Color(10, 10, 10, 190));
	}
	else if (Settings::ESP::Boxes::type == BoxType::FLAT_2D)
	{
		// color
		Draw::Rectangle(x, y, x + w, y + h, color);
		// outer outline
		Draw::Rectangle(x + 1, y + 1, x + w - 1, y + h - 1, Color(10, 10, 10, 190));
		// inner outline
		Draw::Rectangle(x - 1, y - 1, x + w + 1, y + h + 1, Color(10, 10, 10, 190));
	}
	else if (Settings::ESP::Boxes::type == BoxType::BOX_3D)
	{
		Vector vOrigin = entity->GetVecOrigin();
		Vector min = entity->GetCollideable()->OBBMins() + vOrigin;
		Vector max = entity->GetCollideable()->OBBMaxs() + vOrigin;

		Vector points[] = { Vector(min.x, min.y, min.z),
		                    Vector(min.x, max.y, min.z),
		                    Vector(max.x, max.y, min.z),
		                    Vector(max.x, min.y, min.z),
		                    Vector(min.x, min.y, max.z),
		                    Vector(min.x, max.y, max.z),
		                    Vector(max.x, max.y, max.z),
		                    Vector(max.x, min.y, max.z) };

		int edges[12][2] = { { 0, 1 }, { 1, 2 }, { 2, 3 }, { 3, 0 },
		                     { 4, 5 }, { 5, 6 }, { 6, 7 }, { 7, 4 },
		                     { 0, 4 }, { 1, 5 }, { 2, 6 }, { 3, 7 }, };

		for (auto it : edges)
		{
			Vector p1, p2;
			if (debugOverlay->ScreenPosition(points[it[0]], p1) || debugOverlay->ScreenPosition(points[it[1]], p2))
				return;
			Draw::Line(Vector2D(p1.x, p1.y), Vector2D(p2.x, p2.y), color);
		}
	}
}

void ESP::DrawEntity(C_BaseEntity* entity, const char* string, Color color)
{
	int x, y, w, h;
	if (GetBox(entity, x, y, w, h))
	{
		DrawBox(color, x, y, w, h, entity);

		Vector2D nameSize = Draw::GetTextSize(string, esp_font);
		Draw::Text((int)(x + (w / 2) - (nameSize.x / 2)), y + h + 2, string, esp_font, Color(255, 255, 255, 255));
	}
}

void ESP::DrawPlayer(int index, C_BasePlayer* player, IEngineClient::player_info_t player_info)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	if (player == localplayer && !Settings::ESP::Filters::localplayer)
		return;

	if (player->GetTeam() != localplayer->GetTeam() && !Settings::ESP::Filters::enemies)
		return;

	if (player != localplayer && player->GetTeam() == localplayer->GetTeam() && !Settings::ESP::Filters::allies)
		return;

	bool bIsVisible = false;
	if (Settings::ESP::Filters::visibilityCheck || Settings::ESP::Filters::legit)
	{
		bIsVisible = Entity::IsVisible(player, Bone::BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck);
		if (!bIsVisible && Settings::ESP::Filters::legit)
			return;
	}

	ImColor playerColor = GetESPPlayerColor(player, bIsVisible);

	static Vector2D textSize = Draw::GetTextSize("Hi", esp_font);

	int x, y, w, h;
	if (!GetBox(player, x, y, w, h))
		return;

	if (Settings::ESP::Boxes::enabled)
		DrawBox(Color::FromImColor(playerColor), x, y, w, h, player);

	int boxSpacing = Settings::ESP::Boxes::enabled ? 3 : 0;
	Vector2D barsSpacing = Vector2D(0, 0);

	// draw bars
	if (Settings::ESP::Bars::enabled)
	{
		Color barColor;

		// clamp it to 100
		int HealthValue = std::max(0, std::min(player->GetHealth(), 100));
		float HealthPerc = HealthValue / 100.f;

		int barx = x;
		int bary = y;
		int barw = w;
		int barh = h;

		if (Settings::ESP::Bars::colorType == BarColorType::HEALTH_BASED)
			barColor = Util::GetHealthColor(HealthValue);
		else if (Settings::ESP::Bars::colorType== BarColorType::STATIC_COLOR)
			barColor = Color::FromImColor(playerColor);

		if (Settings::ESP::Bars::type == BarType::VERTICAL)
		{
			barw = 4; // outline(1px) + bar(2px) + outline(1px) = 6px;
			barx -= barw + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 8 px

			Draw::Rectangle(barx - 1, bary - 1, barx + barw + 1, bary + barh + 1, Color(255, 255, 255, 170));
			Draw::FilledRectangle(barx, bary, barx + barw, bary + barh, Color(10, 10, 10, 255));

			if (HealthPerc > 0)
				Draw::FilledRectangle(barx + 1, bary + (barh * (1.f - HealthPerc)) + 1, barx + barw - 1, bary + barh - 1, barColor);

			barsSpacing.x += barw;
		}
		else if (Settings::ESP::Bars::type == BarType::VERTICAL_RIGHT)
		{
			barx += barw + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 8 px
			barw = 4; // outline(1px) + bar(2px) + outline(1px) = 6px;

			Draw::Rectangle(barx - 1, bary - 1, barx + barw + 1, bary + barh + 1, Color(255, 255, 255, 170));
			Draw::FilledRectangle(barx, bary, barx + barw, bary + barh, Color(10, 10, 10, 255));

			if (HealthPerc > 0)
				Draw::FilledRectangle(barx + 1, bary + (barh * (1.f - HealthPerc)) + 1, barx + barw - 1, bary + barh - 1, barColor);

			barsSpacing.x += barw;
		}
		else if (Settings::ESP::Bars::type == BarType::HORIZONTAL)
		{
			bary += barh + boxSpacing; // player box(?px) + spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 5 px
			barh = 4; // outline(1px) + bar(2px) + outline(1px) = 4px;

			Draw::Rectangle(barx - 1, bary - 1, barx + barw + 1, bary + barh + 1, Color(255, 255, 255, 170));
			Draw::FilledRectangle(barx, bary, barx + barw, bary + barh, Color(10, 10, 10, 255));

			if (HealthPerc > 0)
			{
				barw *= HealthPerc;
				Draw::Rectangle(barx + 1, bary + 1, barx + barw - 1, bary + barh - 1, barColor);
			}
			barsSpacing.y += barh;
		}
		else if (Settings::ESP::Bars::type == BarType::HORIZONTAL_UP)
		{
			barh = 4; // outline(1px) + bar(2px) + outline(1px) = 4px;
			bary -= barh + boxSpacing; // spacing(1px) + outline(1px) + bar(2px) + outline (1px) = 5 px

			Draw::Rectangle(barx - 1, bary - 1, barx + barw + 1, bary + barh + 1, Color(255, 255, 255, 170));
			Draw::FilledRectangle(barx, bary, barx + barw, bary + barh, Color(10, 10, 10, 255));

			if (HealthPerc > 0)
			{
				barw *= HealthPerc;
				Draw::Rectangle(barx + 1, bary + 1, barx + barw - 1, bary + barh - 1, barColor);
			}
			barsSpacing.y += barh;
		}
		else if (Settings::ESP::Bars::type == BarType::INTERWEBZ)
		{
			// pasted from ayyware and broken ( bg is 1px off to the left ) idc
			bary += barh + boxSpacing;
			barh = 4;

			float Width = (w * HealthPerc);
			barw = (int)(Width);

			Vertex_t Verts[4];
			Verts[0].Init(Vector2D(barx, bary));
			Verts[1].Init(Vector2D(barx + w + 5, bary));
			Verts[2].Init(Vector2D(barx + w, bary + 5));
			Verts[3].Init(Vector2D(barx - 5, bary + 5));

			Draw::TexturedPolygon(4, Verts, Color(10, 10, 10, 255));
			Draw::PolyLine(Verts, 4, Color(255, 255, 255, 170));

			Vertex_t Verts2[4];
			Verts2[0].Init(Vector2D(barx + 1, bary + 1));
			Verts2[1].Init(Vector2D(barx + barw + 5, bary + 1));
			Verts2[2].Init(Vector2D(barx + barw, bary + 5));
			Verts2[3].Init(Vector2D(barx - 4, bary + 5));

			Draw::TexturedPolygon(4, Verts2, barColor);

			Verts2[0].Init(Vector2D(barx + 1, bary + 1));
			Verts2[1].Init(Vector2D(barx + barw + 2, bary + 1));
			Verts2[2].Init(Vector2D(barx + barw, bary + 2));
			Verts2[3].Init(Vector2D(barx - 2, bary + 2));

			Draw::TexturedPolygon(4, Verts2, Color(255, 255, 255, 40));

			barsSpacing.y += barh;
		}
	}

	// draw name
	int multiplier = 1;
	int nameOffset = (int)(Settings::ESP::Bars::type == BarType::HORIZONTAL_UP ? boxSpacing + barsSpacing.y : 0);

	if (Settings::ESP::Info::name || Settings::ESP::Info::clan)
	{
		std::string displayString;

		if (Settings::ESP::Info::clan)
			displayString += std::string((*csPlayerResource)->GetClan(index));

		if (Settings::ESP::Info::clan && Settings::ESP::Info::name)
			displayString += " ";

		if (Settings::ESP::Info::name)
			displayString += player_info.name;

		Vector2D nameSize = Draw::GetTextSize(displayString.c_str(), esp_font);
		Draw::Text((int)(x + (w / 2) - (nameSize.x / 2)), (int)(y - textSize.y - nameOffset), displayString.c_str(), esp_font, Color(255, 255, 255));
		multiplier++;
	}

	// draw steamid
	if (Settings::ESP::Info::steamId)
	{
		Vector2D rankSize = Draw::GetTextSize(player_info.guid, esp_font);
		Draw::Text((int)(x + (w / 2) - (rankSize.x / 2)), (int)(y - (textSize.y * multiplier) - nameOffset), player_info.guid, esp_font, Color(255, 255, 255, 255));
		multiplier++;
	}

	// draw rank
	if (Settings::ESP::Info::rank)
	{
		int rank = *(*csPlayerResource)->GetCompetitiveRanking(index);

		if (rank >= 0 && rank < 19)
		{
			Vector2D rankSize = Draw::GetTextSize(ESP::ranks[rank], esp_font);
			Draw::Text((int)(x + (w / 2) - (rankSize.x / 2)), (int)(y - (textSize.y * multiplier) - nameOffset), ESP::ranks[rank], esp_font, Color(255, 255, 255, 255));
		}
	}

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(player->GetActiveWeapon());

	// health
	if (Settings::ESP::Info::health)
	{
		std::string buf = std::to_string(player->GetHealth()) + " HP";
		Draw::Text(x + w + boxSpacing, (int)(y + h - textSize.y), buf.c_str(), esp_font, Color(255, 255, 255));
	}

	// weapon
	if (Settings::ESP::Info::weapon && activeWeapon)
	{
		std::string modelName = Util::Items::GetItemDisplayName(*activeWeapon->GetItemDefinitionIndex());
		int offset = (int)(Settings::ESP::Bars::type == BarType::HORIZONTAL || Settings::ESP::Bars::type == BarType::INTERWEBZ ? boxSpacing + barsSpacing.y + 1 : 0);

		Vector2D weaponTextSize = Draw::GetTextSize(modelName.c_str(), esp_font);
		Draw::Text((int)(x + (w / 2) - (weaponTextSize.x / 2)), y + h + offset, modelName.c_str(), esp_font, Color(255, 255, 255));
	}

	// draw info
	std::vector<std::string> stringsToShow;

	if (Settings::ESP::Info::scoped && player->IsScoped())
		stringsToShow.push_back("Scoped");

	if (Settings::ESP::Info::reloading && activeWeapon && activeWeapon->GetInReload())
		stringsToShow.push_back("Reloading");

	if (Settings::ESP::Info::flashed && player->GetFlashBangTime() - globalVars->curtime > 2.0f)
		stringsToShow.push_back("Flashed");

	if (Settings::ESP::Info::planting && Entity::IsPlanting(player))
		stringsToShow.push_back("Planting");

	if (Settings::ESP::Info::planting && index == (*csPlayerResource)->GetPlayerC4())
		stringsToShow.push_back("Bomb Carrier");

	if (Settings::ESP::Info::hasDefuser && player->HasDefuser())
		stringsToShow.push_back("Defuse kit");

	if (Settings::ESP::Info::defusing && player->IsDefusing())
		stringsToShow.push_back("Defusing");

	if (Settings::ESP::Info::grabbingHostage && player->IsGrabbingHostage())
		stringsToShow.push_back("Hostage Carrier");

	if (Settings::ESP::Info::rescuing && player->IsRescuing())
		stringsToShow.push_back("Rescuing");

	if (Settings::ESP::Info::location)
		stringsToShow.push_back(player->GetLastPlaceName());

	int i = 0;
	for (auto Text : stringsToShow)
	{
		Draw::Text(x + w + boxSpacing, (int)(y + (i * (textSize.y + 2))), Text.c_str(), esp_font, Color(255, 255, 255));
		i++;
	}

	if (Settings::ESP::Skeleton::enabled)
		DrawSkeleton(player);

	if (Settings::ESP::BulletTracers::enabled)
		DrawBulletTrace(player);

	if (Settings::ESP::Tracers::enabled && player != localplayer)
		DrawTracer(player);

	if (Settings::ESP::HeadDot::enabled)
		DrawHeaddot(player);
}

void ESP::DrawBomb(C_BaseCombatWeapon* bomb)
{
	if (!(*csGameRules) || !(*csGameRules)->IsBombDropped())
		return;

	DrawEntity(bomb, "Bomb", Color::FromImColor(Settings::ESP::bombColor.Color()));
}

void ESP::DrawPlantedBomb(C_PlantedC4* bomb)
{
	if (!(*csGameRules) || !(*csGameRules)->IsBombPlanted())
		return;

	ImColor color = bomb->GetBombDefuser() != -1 || bomb->IsBombDefused() ? Settings::ESP::bombDefusingColor.Color() : Settings::ESP::bombColor.Color();

	float bombTimer = bomb->GetBombTime() - globalVars->curtime;
	std::stringstream displayText;
	if (bomb->IsBombDefused() || !bomb->IsBombTicking() || bombTimer <= 0.f)
	{
			displayText << "Bomb";
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

		displayText << "Bomb: " << std::fixed << std::showpoint << std::setprecision(1) << bombTimer << ", damage: " << (int) damage;
	}

	DrawEntity(bomb, displayText.str().c_str(), Color::FromImColor(color));
}

void ESP::DrawDefuseKit(C_BaseEntity* defuser)
{
	DrawEntity(defuser, "Defuser", Color::FromImColor(Settings::ESP::defuserColor.Color()));
}

void ESP::DrawDroppedWeapons(C_BaseCombatWeapon* weapon)
{
	Vector vOrig = weapon->GetVecOrigin();
	int owner = weapon->GetOwner();

	if (owner > -1 || (vOrig.x == 0 && vOrig.y == 0 && vOrig.z == 0))
		return;

	std::string modelName = Util::Items::GetItemDisplayName(*weapon->GetItemDefinitionIndex());

	if (weapon->GetAmmo() > 0)
	{
		modelName += " | ";
		modelName += std::to_string(weapon->GetAmmo());
	}

	DrawEntity(weapon, modelName.c_str(), Color::FromImColor(Settings::ESP::weaponColor.Color()));
}

void ESP::DrawHostage(C_BaseEntity* hostage)
{
	DrawEntity(hostage, "Hostage", Color::FromImColor(Settings::ESP::hostageColor.Color()));
}

void ESP::DrawChicken(C_BaseEntity* chicken)
{
	DrawEntity(chicken, "Chicken", Color::FromImColor(Settings::ESP::chickenColor.Color()));
}

void ESP::DrawFish(C_BaseEntity* fish)
{
	DrawEntity(fish, "Fish", Color::FromImColor(Settings::ESP::fishColor.Color()));
}

void ESP::DrawThrowable(C_BaseEntity* throwable, ClientClass* client)
{
	model_t* nadeModel = throwable->GetModel();

	if (!nadeModel)
		return;

	studiohdr_t* hdr = modelInfo->GetStudioModel(nadeModel);

	if (!hdr)
		return;

	if (!strstr(hdr->name, "thrown") && !strstr(hdr->name, "dropped"))
		return;

	ImColor nadeColor = ImColor(255, 255, 255, 255);
	std::string nadeName = "Unknown Grenade";

	IMaterial* mats[32];
	modelInfo->GetModelMaterials(nadeModel, hdr->numtextures, mats);

	for (int i = 0; i < hdr->numtextures; i++)
	{
		IMaterial* mat = mats[i];
		if (!mat)
			continue;

		if (strstr(mat->GetName(), "flashbang"))
		{
			nadeName = "Flashbang";
			nadeColor = Settings::ESP::flashbangColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), "m67_grenade") || strstr(mat->GetName(), "hegrenade"))
		{
			nadeName = "HE Grenade";
			nadeColor = Settings::ESP::grenadeColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), "smoke"))
		{
			nadeName = "Smoke";
			nadeColor = Settings::ESP::smokeColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), "decoy"))
		{
			nadeName = "Decoy";
			nadeColor = Settings::ESP::decoyColor.Color();
			break;
		}
		else if (strstr(mat->GetName(), "incendiary") || strstr(mat->GetName(), "molotov"))
		{
			nadeName = "Molotov";
			nadeColor = Settings::ESP::molotovColor.Color();
			break;
		}
	}

	DrawEntity(throwable, nadeName.c_str(), Color::FromImColor(nadeColor));
}

void ESP::DrawSkeleton(C_BasePlayer* player)
{
	studiohdr_t* pStudioModel = modelInfo->GetStudioModel(player->GetModel());
	if (!pStudioModel)
		return;

	static matrix3x4_t pBoneToWorldOut[128];
	if (player->SetupBones(pBoneToWorldOut, 128, 256, 0))
	{
		for (int i = 0; i < pStudioModel->numbones; i++)
		{
			mstudiobone_t* pBone = pStudioModel->pBone(i);
			if (!pBone || !(pBone->flags & 256) || pBone->parent == -1)
				continue;

			Vector vBonePos1;
			if (debugOverlay->ScreenPosition(Vector(pBoneToWorldOut[i][0][3], pBoneToWorldOut[i][1][3], pBoneToWorldOut[i][2][3]), vBonePos1))
				continue;

			Vector vBonePos2;
			if (debugOverlay->ScreenPosition(Vector(pBoneToWorldOut[pBone->parent][0][3], pBoneToWorldOut[pBone->parent][1][3], pBoneToWorldOut[pBone->parent][2][3]), vBonePos2))
				continue;

			Draw::Line(Vector2D(vBonePos1.x, vBonePos1.y), Vector2D(vBonePos2.x, vBonePos2.y), Color::FromImColor(Settings::ESP::Skeleton::color.Color()));
		}
	}
}

void ESP::DrawBulletTrace(C_BasePlayer* player)
{
	Vector src3D, dst3D, forward, src, dst;
	trace_t tr;
	Ray_t ray;
	CTraceFilter filter;

	Math::AngleVectors(*player->GetEyeAngles(), forward);
	filter.pSkip = player;
	src3D = player->GetEyePosition();
	dst3D = src3D + (forward * 8192);

	ray.Init(src3D, dst3D);

	trace->TraceRay(ray, MASK_SHOT, &filter, &tr);

	if (debugOverlay->ScreenPosition(src3D, src) || debugOverlay->ScreenPosition(tr.endpos, dst))
		return;

	Draw::Line((int)(src.x), (int)(src.y), (int)(dst.x), (int)(dst.y), Color::FromImColor(GetESPPlayerColor(player, true)));
	Draw::FilledRectangle((int)(dst.x - 3), (int)(dst.y - 3), 6, 6, Color::FromImColor(GetESPPlayerColor(player, false)));
}

void ESP::DrawTracer(C_BasePlayer* player)
{
	Vector src3D, src;
	src3D = player->GetVecOrigin() - Vector(0, 0, 0);

	if (debugOverlay->ScreenPosition(src3D, src))
		return;

	int ScreenWidth, ScreenHeight;
	engine->GetScreenSize(ScreenWidth, ScreenHeight);

	int x = (int)(ScreenWidth * 0.5f);
	int y = 0;

	if (Settings::ESP::Tracers::type == TracerType::CURSOR)
		y = (int)(ScreenHeight * 0.5f);
	else if (Settings::ESP::Tracers::type == TracerType::BOTTOM)
		y = ScreenHeight;

	bool bIsVisible = Entity::IsVisible(player, Bone::BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck);
	Draw::Line((int)(src.x), (int)(src.y), x, y, Color::FromImColor(GetESPPlayerColor(player, bIsVisible)));
}

void ESP::DrawHeaddot(C_BasePlayer* player)
{
	Vector head2D;
	Vector head3D = player->GetBonePosition((int) Bone::BONE_HEAD);
	if (debugOverlay->ScreenPosition(Vector(head3D.x, head3D.y, head3D.z), head2D))
		return;

	bool bIsVisible = false;
	if (Settings::ESP::Filters::visibilityCheck || Settings::ESP::Filters::legit)
		bIsVisible = Entity::IsVisible(player, Bone::BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck);

	Draw::FilledCircle(Vector2D(head2D.x, head2D.y), 10, Settings::ESP::HeadDot::size, Color::FromImColor(GetESPPlayerColor(player, bIsVisible)));
}

void ESP::CollectFootstep(int iEntIndex, const char *pSample)
{
	if (strstr(pSample, "player/footsteps") == NULL && strstr(pSample, "player/land") == NULL)
		return;

	if (iEntIndex == engine->GetLocalPlayer())
		return;

	Footstep footstep;
	footstep.entityId = iEntIndex;
	footstep.position = entityList->GetClientEntity(iEntIndex)->GetVecOrigin();

	footstep.expiration = Util::GetEpochTime() + Settings::ESP::Sounds::time;

	footsteps.push_back(footstep);
}

void ESP::DrawSounds()
{
	for (unsigned int i = 0; i < footsteps.size(); i++)
	{
		long diff = footsteps[i].expiration - Util::GetEpochTime();

		if (diff <= 0)
		{
			footsteps.erase(footsteps.begin() + i);
			continue;
		}

		Vector pos2d;

		if (debugOverlay->ScreenPosition(footsteps[i].position, pos2d))
			continue;

		C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
		if (!localplayer)
			continue;

		C_BasePlayer* player = (C_BasePlayer*) entityList->GetClientEntity(footsteps[i].entityId);
		if (!player)
			continue;

		if (player->GetTeam() != localplayer->GetTeam() && !Settings::ESP::Filters::enemies)
			continue;

		if (player->GetTeam() == localplayer->GetTeam() && !Settings::ESP::Filters::allies)
			continue;

		bool bIsVisible = false;
		if (Settings::ESP::Filters::visibilityCheck || Settings::ESP::Filters::legit)
			bIsVisible = Entity::IsVisible(player, Bone::BONE_HEAD, 180.f, Settings::ESP::Filters::smokeCheck);

		float percent = (float)diff / (float)Settings::ESP::Sounds::time;

		Color playerColor = Color::FromImColor(GetESPPlayerColor(player, bIsVisible));
		playerColor.a = std::min(powf(percent * 2, 0.6f), 1.f) * playerColor.a; // fades out alpha when its below 0.5

		float circleRadius = fabs(percent - 1.f) * 42.f;
		float points = circleRadius * 0.75f;

		Draw::Circle3D(footsteps[i].position, points, circleRadius, playerColor);
	}
}

void ESP::DrawFOVCrosshair()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer->GetAlive())
		return;

	int width, height;
	engine->GetScreenSize(width, height);

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

		radius = fabsf(width / 2 - max2D.x);
	}
	else
	{
		float aimbotFov = Settings::Aimbot::AutoAim::fov;
		float fov = OverrideView::currentFOV;
		radius = tanf(DEG2RAD(aimbotFov) / 2) / tanf(DEG2RAD(fov) / 2) * width;
	}
	
	if (Settings::ESP::FOVCrosshair::filled)
		Draw::FilledCircle(Vector2D(width / 2, height / 2), 20, radius, Color::FromImColor(Settings::ESP::FOVCrosshair::color.Color()));
	else
		Draw::Circle(Vector2D(width / 2, height / 2), 20, radius, Color::FromImColor(Settings::ESP::FOVCrosshair::color.Color()));
}

void ESP::DrawGlow()
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
				if (glow_object.m_pEntity->GetTeam() != localplayer->GetTeam())
				{
					if (Entity::IsVisible(player, Bone::BONE_HEAD))
						color = Settings::ESP::Glow::enemyVisibleColor.Color(player);
					else
						color = Settings::ESP::Glow::enemyColor.Color(player);
				}
				else
					color = Settings::ESP::Glow::allyColor.Color(player);
			}
		}
		else if (client->m_ClassID != EClassIds::CBaseWeaponWorldModel &&
				 (strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == EClassIds::CDEagle || client->m_ClassID == EClassIds::CAK47))
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

bool ESP::PrePaintTraverse(VPANEL vgui_panel, bool force_repaint, bool allow_force)
{
	if (Settings::ESP::enabled && Settings::NoScopeBorder::enabled && strcmp("HudZoom", panel->GetName(vgui_panel)) == 0)
		return false;

	return true;
}

void ESP::Paint()
{
	if (!Settings::ESP::enabled)
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

			IEngineClient::player_info_t playerInfo;
			if (engine->GetPlayerInfo(i, &playerInfo))
				DrawPlayer(i, player, playerInfo);
		}
		if ((client->m_ClassID != EClassIds::CBaseWeaponWorldModel && (strstr(client->m_pNetworkName, "Weapon") || client->m_ClassID == EClassIds::CDEagle || client->m_ClassID == EClassIds::CAK47)) && Settings::ESP::Filters::weapons)
		{
			C_BaseCombatWeapon* weapon = (C_BaseCombatWeapon*) entity;
			DrawDroppedWeapons(weapon);
		}
		else if (client->m_ClassID == EClassIds::CC4 && Settings::ESP::Filters::bomb)
		{
			C_BaseCombatWeapon* bomb = (C_BaseCombatWeapon*) entity;
			DrawBomb(bomb);
		}
		else if (client->m_ClassID == EClassIds::CPlantedC4 && Settings::ESP::Filters::bomb)
		{
			C_PlantedC4* pC4 = (C_PlantedC4*) entity;
			DrawPlantedBomb(pC4);
		}
		else if (client->m_ClassID == EClassIds::CHostage && Settings::ESP::Filters::hostages)
		{
			DrawHostage(entity);
		}
		else if (client->m_ClassID == EClassIds::CBaseAnimating && Settings::ESP::Filters::defusers)
		{
			DrawDefuseKit(entity);
		}
		else if (client->m_ClassID == EClassIds::CChicken && Settings::ESP::Filters::chickens)
		{
			DrawChicken(entity);
		}
		else if (client->m_ClassID == EClassIds::CFish && Settings::ESP::Filters::fishes)
		{
			DrawFish(entity);
		}
		else if (Settings::ESP::Filters::throwables && strstr(client->m_pNetworkName, "Projectile"))
		{
			DrawThrowable(entity, client);
		}
	}

	if (Settings::ESP::Sounds::enabled)
		ESP::DrawSounds();

	if (Settings::ESP::FOVCrosshair::enabled)
		ESP::DrawFOVCrosshair();

	if (Settings::NoScopeBorder::enabled && localplayer->IsScoped())
		ESP::DrawScope();
}

void ESP::DrawModelExecute(void* thisptr, void* context, void *state, const ModelRenderInfo_t &pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	if (!Settings::ESP::enabled)
		return;

	if (!engine->IsInGame())
		return;

	if (Settings::ESP::Glow::enabled)
		ESP::DrawGlow();
}

void ESP::EmitSound(int iEntIndex, const char *pSample)
{
	if (Settings::ESP::Sounds::enabled)
		ESP::CollectFootstep(iEntIndex, pSample);
}

void ESP::DrawScope()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	if (*activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_SG556 || *activeWeapon->GetItemDefinitionIndex() == ItemDefinitionIndex::WEAPON_AUG)
		return;

	int width, height;
	engine->GetScreenSize(width, height);

	Draw::Line(0, height * 0.5, width, height * 0.5, Color(0, 0, 0, 255));
	Draw::Line(width * 0.5, 0, width * 0.5, height, Color(0, 0, 0, 255));
}

void ESP::CreateMove(CUserCmd* cmd)
{
	viewanglesBackup = cmd->viewangles;
}
