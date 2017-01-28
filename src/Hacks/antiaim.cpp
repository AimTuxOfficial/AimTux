#include "antiaim.h"

bool Settings::AntiAim::Yaw::enabled = false;
bool Settings::AntiAim::Pitch::enabled = false;
int Settings::AntiAim::Yaw::type = SPIN_FAST;
int Settings::AntiAim::Yaw::type_fake = SPIN_FAST;
int Settings::AntiAim::Pitch::type = STATIC_DOWN;
bool Settings::AntiAim::HeadEdge::enabled = false;
float Settings::AntiAim::HeadEdge::distance = 25.0f;
bool Settings::AntiAim::AutoDisable::no_enemy = false;
bool Settings::AntiAim::AutoDisable::knife_held = false;

float Distance(Vector a, Vector b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

bool AntiAim::GetBestHeadAngle(QAngle& angle)
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());

	Vector position = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();

	float closest_distance = 100.0f;

	float radius = Settings::AntiAim::HeadEdge::distance + 0.1f;
	float step = M_PI * 2.0 / 8;

	for (float a = 0; a < (M_PI * 2.0); a += step)
	{
		Vector location(radius * cos(a) + position.x, radius * sin(a) + position.y, position.z);

		Ray_t ray;
		trace_t tr;
		ray.Init(position, location);
		CTraceFilter traceFilter;
		traceFilter.pSkip = localplayer;
		trace->TraceRay(ray, 0x4600400B, &traceFilter, &tr);

		float distance = Distance(position, tr.endpos);

		if (distance < closest_distance)
		{
			closest_distance = distance;
			angle.y = RAD2DEG(a);
		}
	}

	return closest_distance < Settings::AntiAim::HeadEdge::distance;
}

bool HasViableEnemy()
{
	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());

	for (int i = 1; i < engine->GetMaxClients(); ++i)
	{
		C_BasePlayer* entity = (C_BasePlayer*) entitylist->GetClientEntity(i);

		if (!entity
			|| entity == localplayer
			|| entity->GetDormant()
			|| !entity->GetAlive()
			|| entity->GetImmune())
			continue;

		IEngineClient::player_info_t entityInformation;
		engine->GetPlayerInfo(i, &entityInformation);

		if (std::find(Aimbot::Friends.begin(), Aimbot::Friends.end(), entityInformation.xuid) != Aimbot::Friends.end())
			continue;

		if (Settings::Aimbot::friendly || entity->GetTeam() != localplayer->GetTeam())
			return true;
	}

	return false;
}

void DoAntiAimY(QAngle& angle, int command_number, bool bFlip, bool& clamp)
{
	int aa_type = bFlip ? Settings::AntiAim::Yaw::type_fake : Settings::AntiAim::Yaw::type;

	static bool yFlip;
	float temp;
	double factor;
	static float trigger;
	QAngle temp_qangle;

	if (bFlip)
		yFlip = !yFlip;

	switch (aa_type)
	{
		case AntiAimType_Y::SPIN_FAST:
			factor =  360.0 / M_PHI;
			factor *= 25;
			angle.y = fmod(globalvars->curtime * factor, 360.0);
			break;
		case AntiAimType_Y::SPIN_SLOW:
			factor =  360.0 / M_PHI;
			angle.y = fmod(globalvars->curtime * factor, 360.0);
			break;
		case AntiAimType_Y::JITTER:
			yFlip ? angle.y -= 90.0f : angle.y -= 270.0f;
			break;
		case AntiAimType_Y::SIDE:
			yFlip ? angle.y += 90.f : angle.y -= 90.0f;
			break;
		case AntiAimType_Y::BACKWARDS:
			angle.y -= 180.0f;
			break;
		case AntiAimType_Y::FORWARDS:
			angle.y -= 0.0f;
			break;
		case AntiAimType_Y::LEFT:
			angle.y += 90.0f;
			break;
		case AntiAimType_Y::RIGHT:
			angle.y -= 90.0f;
			break;
		case AntiAimType_Y::STATICAA:
			angle.y = 0.0f;
			break;
		case AntiAimType_Y::STATICJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? 150.0f : -150.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimType_Y::STATICSMALLJITTER:
			trigger += 15.0f;
			angle.y = trigger > 50.0f ? -30.0f : 30.0f;

			if (trigger > 100.0f)
				trigger = 0.0f;
			break;
		case AntiAimType_Y::LISP:
			clamp = false;
			yFlip ? angle.y += 323210000.0f : angle.y -= 323210000.0f;
			break;
		case AntiAimType_Y::LISP_SIDE:
			clamp = false;
			temp = angle.y + 90.0f;
			temp_qangle = QAngle(0.0f, temp, 0.0f);
			Math::NormalizeAngles(temp_qangle);
			temp = temp_qangle.y;

			if (temp > -45.0f)
				temp < 0.0f ? temp = -90.0f : temp < 45.0f ? temp = 90.0f : temp = temp;

			temp += 1800000.0f;
			angle.y = temp;
			break;
		case AntiAimType_Y::LISP_JITTER:
			clamp = false;
			static int jittertimer = -1;
			temp = angle.y - 155.0f;

			if (jittertimer == 1)
			{
				temp = angle.y + 58.0f;
				temp += 1800000.0f;
			}

			if (bSendPacket)
			{
				if (jittertimer >= 1)
					jittertimer = -1;
				jittertimer++;
			}
			angle.y = temp;
			break;
		case AntiAimType_Y::ANGEL_BACKWARD:
			clamp = false;
			angle.y += 36000180.0f;
			break;
		case AntiAimType_Y::ANGEL_INVERSE:
			clamp = false;
			angle.y = 36000180.0f;
			break;
		case AntiAimType_Y::ANGEL_SPIN:
			clamp = false;
			factor = (globalvars->curtime * 5000.0f);
			angle.y = factor + 36000000.0f;
			break;
		default:
			angle.y -= 0.0f;
			break;
	}
}

void DoAntiAimX(QAngle& angle, bool bFlip, bool& clamp)
{
	static float pDance = 0.0f;
	int aa_type = Settings::AntiAim::Pitch::type;

	switch (aa_type)
	{
		case AntiAimType_X::STATIC_UP:
			angle.x = -89.0f;
			break;
		case AntiAimType_X::STATIC_DOWN:
			angle.x = 89.0f;
			break;
		case AntiAimType_X::DANCE:
			pDance += 45.0f;
			if (pDance > 100)
				pDance = 0.0f;
			else if (pDance > 75.f)
				angle.x = -89.f;
			else if (pDance < 75.f)
				angle.x = 89.f;
			break;
		case AntiAimType_X::FRONT:
			angle.x = 0.0f;
			break;
		case AntiAimType_X::STATIC_UP_FAKE:
			angle.x = bFlip ? 89.0f : -89.0f;
			break;
		case AntiAimType_X::STATIC_DOWN_FAKE:
			angle.x = bFlip ? -89.0f : 89.0f;
			break;
		case AntiAimType_X::LISP_DOWN:
			clamp = false;
			angle.x = 1800089.0f;
			break;
		case AntiAimType_X::ANGEL_DOWN:
			clamp = false;
			angle.x = 36000088.0f;
			break;
		case AntiAimType_X::ANGEL_UP:
			clamp = false;
			angle.x = 35999912.0f;
			break;
		default:
			angle.x -= 0.0f;
			break;
	}
}

void AntiAim::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AntiAim::Yaw::enabled && !Settings::AntiAim::Pitch::enabled)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::AimStepInProgress)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	C_BasePlayer* localplayer = (C_BasePlayer*) entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*) entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	if (active_weapon->GetCSWpnData()->GetWeaponType() == WEAPONTYPE_GRENADE)
	{
		C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*) active_weapon;

		if (csGrenade->GetThrowTime() > 0.f)
			return;
	}

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	// AutoDisable checks

	// Knife
	if (Settings::AntiAim::AutoDisable::knife_held && localplayer->GetAlive() && active_weapon->GetCSWpnData()->GetWeaponType() == WEAPONTYPE_KNIFE)
		return;

	if (Settings::AntiAim::AutoDisable::no_enemy && localplayer->GetAlive() && !HasViableEnemy())
		return;

	QAngle edge_angle = angle;
	bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

	static bool bFlip;

	bFlip = !bFlip;

	bool should_clamp = true;

	if (!ValveDSCheck::forceUT && (*csGameRules) && (*csGameRules)->IsValveDS())
	{
		if (Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
			Settings::AntiAim::Yaw::type = SPIN_SLOW;

		if (Settings::AntiAim::Yaw::type_fake >= AntiAimType_Y::LISP)
			Settings::AntiAim::Yaw::type_fake = SPIN_SLOW;

		if (Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
			Settings::AntiAim::Pitch::type = STATIC_UP;
	}

	if (Settings::AntiAim::Yaw::enabled)
	{
		DoAntiAimY(angle, cmd->command_number, bFlip, should_clamp);
		Math::NormalizeAngles(angle);
		CreateMove::SendPacket = bFlip;
		if (Settings::AntiAim::HeadEdge::enabled && edging_head && !bFlip)
			angle.y = edge_angle.y;
	}

	if (Settings::AntiAim::Pitch::enabled)
		DoAntiAimX(angle, bFlip, should_clamp);

	if (should_clamp)
	{
		Math::NormalizeAngles(angle);
		Math::ClampAngles(angle);
	}

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
