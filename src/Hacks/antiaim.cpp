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
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

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
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());

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
	int aa_type = bFlip ? Settings::AntiAim::Yaw::type : Settings::AntiAim::Yaw::type_fake;

	static float fYaw = 0.0f;
	static bool yFlip;

	if (bFlip)
		yFlip = !yFlip;

	if (aa_type == AntiAimType_Y::SPIN_FAST || aa_type == AntiAimType_Y::SPIN_SLOW)
	{
		fYaw += aa_type == AntiAimType_Y::SPIN_FAST ? 40.0f : 5.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.y = fYaw;
	}
	else if (aa_type == AntiAimType_Y::JITTER)
		angle.y = yFlip ? 270.0f : 90.0f;
	else if (aa_type == AntiAimType_Y::SIDE)
		if (yFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	else if (aa_type == AntiAimType_Y::BACKWARDS)
		angle.y -= 180.0f;
	else if (aa_type == AntiAimType_Y::FORWARDS)
		angle.y -= 0.0f;
	else if (aa_type == AntiAimType_Y::LEFT)
		angle.y += 90.0f;
	else if (aa_type == AntiAimType_Y::RIGHT)
		angle.y -= 90.0f;
	else if (aa_type == AntiAimType_Y::STATICAA)
		angle.y = 0.0f;
	else if (Settings::AntiAim::type_Y == LISP)
	{
		if (!(cmd->buttons & IN_FORWARD && cmd->buttons & IN_BACK && cmd->buttons & IN_MOVELEFT && cmd->buttons & IN_MOVERIGHT && cmd->buttons & IN_JUMP))
	{
		if (yFlip)
			angle.y += 323210000.0f;
		else
			angle.y -= 323210000.0f;

	}	
	else if (aa_type == AntiAimType_Y::LISP_SIDE)
	{
		clamp = false;

		float temp = angle.y  + 90.f;
		QAngle temp_qangle = QAngle(0.0f, temp, 0.0f);
		Math::NormalizeAngles(temp_qangle);
		temp = temp_qangle.y;

		if (temp > -45.f)
		{
			if (temp < 0.0f)
				temp = -90.f;
			else if (temp < 45.f)
				temp = 90.f;
		}
		temp += 1800000.f;
		angle.y = temp;
	}
	else if (aa_type == AntiAimType_Y::LISP_JITTER)
	{
		clamp = false;

		static int jittertimer = -1;
		float temp = angle.y - 155.f;

		if (jittertimer == 1)
		{
			temp = angle.y + 58.f;
			temp += 1800000.f;
		}

		if (bSendPacket)
		{
			if (jittertimer >= 1)
				jittertimer = -1;
			jittertimer++;
		}
		angle.y = temp;
	}
	else if (aa_type == AntiAimType_Y::ANGEL_BACKWARD)
	{
		clamp = false;
		angle.y += 36000180.f;
	}
	else if (aa_type == AntiAimType_Y::ANGEL_INVERSE)
	{
		clamp = false;
		angle.y = 36000180.f;
	}
	else if (aa_type == AntiAimType_Y::ANGEL_SPIN)
	{
		clamp = false;

		float factor = (globalvars->curtime * 5000.f);
		angle.y = factor + 36000000.f;
	}
	else if (aa_type == AntiAimType_Y::ANGEL_FAKE_SPIN)
	{
		clamp = false;

		if (command_number % 2)
			angle.y += 36000180.f;

		float factor = (globalvars->curtime * 5000.f);
		angle.y = factor + 36000000.f;
	}
	else if (aa_type == AntiAimType_Y::ZERO_OUT_Y)
	{
		clamp = false;
		angle.y = 0.0f;
	}
}

void DoAntiAimX(QAngle& angle, bool bFlip, bool& clamp)
{
	static float pDance = 0.0f;
	int pitch_aa_type = Settings::AntiAim::Pitch::type;

	if (pitch_aa_type == AntiAimType_X::STATIC_UP)
		angle.x = -89.0f;
	else if (pitch_aa_type == AntiAimType_X::STATIC_DOWN)
		angle.x = 89.0f;
	else if (pitch_aa_type == AntiAimType_X::DANCE)
	{
		pDance += 15.0f;

		if (pDance > 100)
			pDance = 0.0f;
		else if (pDance > 50.f)
			angle.x = 330.f;
		else if (pDance < 50.f)
			angle.x = 30.f;
	}
	else if (pitch_aa_type == AntiAimType_X::FRONT)
		angle.x = 0.0f;
	else if (pitch_aa_type == AntiAimType_X::STATIC_UP_FAKE)
	{
		angle.x = bFlip ? 89.0f : -89.0f;
		CreateMove::SendPacket = bFlip;
	}
	else if (pitch_aa_type == AntiAimType_X::STATIC_DOWN_FAKE)
	{
		angle.x = bFlip ? -89.0f : 89.0f;
		CreateMove::SendPacket = bFlip;
	}
	else if (pitch_aa_type == AntiAimType_X::LISP_DOWN)
	{
		clamp = false;
		angle.x = 1800089.f;
	}
	else if (pitch_aa_type == AntiAimType_X::ANGEL_DOWN)
	{
		clamp = false;
		angle.x = 36000088.f;
	}
	else if (pitch_aa_type == AntiAimType_X::ANGEL_UP)
	{
		clamp = false;
		angle.x = 35999912.f;
	}
	else if (pitch_aa_type == AntiAimType_X::ZERO_OUT_X)
	{
		clamp = false;
		angle.x = 0.0f;
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

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!active_weapon)
		return;

	if (active_weapon->IsGrenade())
	{
		C_BaseCSGrenade* csGrenade = (C_BaseCSGrenade*)active_weapon;

		if (csGrenade->GetThrowTime() > 0.f)
			return;
	}

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || cmd->buttons & IN_ATTACK2)
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	// AutoDisable checks

	// Knife
	if (Settings::AntiAim::AutoDisable::knife_held && localplayer->GetAlive() && active_weapon->IsKnife())
		return;

	if (Settings::AntiAim::AutoDisable::no_enemy && localplayer->GetAlive() && !HasViableEnemy())
		return;

	QAngle edge_angle = angle;
	bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

	static bool bFlip;

	bFlip = !bFlip;

	bool should_clamp = true;

	if ((*csGameRules) && (*csGameRules)->IsValveDS())
	{
		if (Settings::AntiAim::Yaw::type > AntiAimType_Y::STATICAA)
			Settings::AntiAim::Yaw::type = SPIN_SLOW;

		if (Settings::AntiAim::Yaw::type_fake > AntiAimType_Y::STATICAA)
			Settings::AntiAim::Yaw::type_fake = SPIN_SLOW;

		if (Settings::AntiAim::Pitch::type > AntiAimType_X::FRONT)
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
	{
		DoAntiAimX(angle, bFlip, should_clamp);
	}

	if (should_clamp)
	{
		Math::NormalizeAngles(angle);
		Math::ClampAngles(angle);
	}

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
