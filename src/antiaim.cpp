#include "antiaim.h"

bool Settings::AntiAim::enabled_Y = false;
bool Settings::AntiAim::enabled_X = false;
AntiAimType_Y Settings::AntiAim::type_Y = SPIN_FAST;
AntiAimType_Y Settings::AntiAim::type_fake_Y = SPIN_FAST;
AntiAimType_X Settings::AntiAim::type_X = STATIC_DOWN;
bool Settings::AntiAim::HeadEdge::enabled = false;
float Settings::AntiAim::HeadEdge::distance = 25.0f;

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

void DoAntiAimY(QAngle&  angle, bool bFlip)
{
	AntiAimType_Y aa_type = bFlip ? Settings::AntiAim::type_Y : Settings::AntiAim::type_fake_Y;
	
	static float fYaw = 0.0f;
	
	if (aa_type == SPIN_FAST || aa_type == SPIN_SLOW)
	{
		fYaw += aa_type == SPIN_FAST ? 40.0f : 5.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.y = fYaw;
	}
	else if (aa_type == JITTER)
	{
		angle.y = bFlip ? 270.0f : 90.0f;
	}
	else if (aa_type == SIDE)
	{
		if (bFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	}
	else if (aa_type == BACKWARDS)
	{
		angle.y -= 180.0f;
	}
	else if (aa_type == FORWARDS)
	{
		angle.y -= 0;
	}
	else if (aa_type == LEFT)
	{
		angle.y += 90;
	}
	else if (aa_type == RIGHT)
	{
		angle.y -= 90;
	}
}


void AntiAim::CreateMove(CUserCmd* cmd)
{
	if (!Settings::AntiAim::enabled_Y && !Settings::AntiAim::enabled_X)
		return;

	if (Settings::Aimbot::AimStep::enabled && Aimbot::AimStepInProgress)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;

	QAngle angle = cmd->viewangles;

	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (active_weapon && active_weapon->IsGrenade()))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	QAngle edge_angle = angle;
	bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

	static bool bFlip;

	bFlip = !bFlip;

	if (Settings::AntiAim::enabled_Y)
	{
		DoAntiAimY (angle, bFlip);
		Math::NormalizeAngles(angle);
		CreateMove::SendPacket = bFlip;
	}

	if (Settings::AntiAim::enabled_X)
	{
		if (Settings::AntiAim::type_X == STATIC_UP)
		{
			angle.x = -89.0f;
		}
		else if (Settings::AntiAim::type_X == STATIC_DOWN)
		{
			angle.x = 89.0f;
		}
#ifdef UNTRUSTED_SETTINGS
		else if (Settings::AntiAim::type_X == STATIC_UP_FAKE)
		{
			angle.x = bFlip ? 89.0f : -89.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_X == STATIC_DOWN_FAKE)
		{
			angle.x = bFlip ? -89.0f : 89.0f;
			CreateMove::SendPacket = bFlip;
		}
#endif
	}

	Math::NormalizeAngles(angle);
	Math::ClampAngles(angle);

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}
