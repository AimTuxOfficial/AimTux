#include "antiaim.h"

bool Settings::AntiAim::Yaw::enabled = false;
bool Settings::AntiAim::Pitch::enabled = false;
int Settings::AntiAim::Yaw::type = SPIN_FAST;
int Settings::AntiAim::Yaw::type_fake = SPIN_FAST;
int Settings::AntiAim::Pitch::type = STATIC_DOWN;
bool Settings::AntiAim::HeadEdge::enabled = false;
float Settings::AntiAim::HeadEdge::distance = 25.0f;
bool Settings::AntiAim::FakeOut::enabled = false;

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
	int aa_type = bFlip ? Settings::AntiAim::Yaw::type : Settings::AntiAim::Yaw::type_fake;

	static float fYaw = 0.0f;
	static bool yFlip;

	if (bFlip)
		yFlip = !yFlip;

	if (aa_type == SPIN_FAST || aa_type == SPIN_SLOW)
	{
		fYaw += aa_type == SPIN_FAST ? 40.0f : 5.0f;

		if (fYaw > 180.0f)
			fYaw -= 360.0f;

		angle.y = fYaw;
	}
	else if (aa_type == JITTER)
		angle.y = yFlip ? 270.0f : 90.0f;
	else if (aa_type == SIDE)
		if (yFlip)
			angle.y += 90.0f;
		else
			angle.y -= 90.0f;
	else if (aa_type == BACKWARDS)
		angle.y -= 180.0f;
	else if (aa_type == FORWARDS)
		angle.y -= 0.0f;
	else if (aa_type == LEFT)
		angle.y += 90.0f;
	else if (aa_type == RIGHT)
		angle.y -= 90.0f;
	else if (aa_type == STATICAA)
		angle.y = 0.0f;
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
	C_BaseCombatWeapon* active_weapon = (C_BaseCombatWeapon*)entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon());

	if (cmd->buttons & IN_USE || cmd->buttons & IN_ATTACK || (active_weapon && active_weapon->IsGrenade()))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	QAngle edge_angle = angle;
	bool edging_head = Settings::AntiAim::HeadEdge::enabled && GetBestHeadAngle(edge_angle);

	static bool bFlip;
	static float pDance = 0.0f;
	static float rYaw = 0.0f;

	bFlip = !bFlip;

	if (Settings::AntiAim::Yaw::enabled)
	{
		DoAntiAimY(angle, bFlip);
		Math::NormalizeAngles(angle);
		CreateMove::SendPacket = bFlip;
		if (Settings::AntiAim::HeadEdge::enabled && edging_head && Settings::AntiAim::FakeOut::enabled)
		{
			if (Settings::AntiAim::Yaw::type == Settings::AntiAim::Yaw::type_fake || !bFlip)
				angle.y = edge_angle.y;
			else if (Settings::AntiAim::Yaw::type == Settings::AntiAim::Yaw::type_fake || bFlip)
			{
				rYaw += 70.0f;

				if (rYaw > 180.0f)
					rYaw -= 360.0f;

				angle.y = rYaw;
			}
		}
		else if ((Settings::AntiAim::HeadEdge::enabled && edging_head && !Settings::AntiAim::FakeOut::enabled) && (Settings::AntiAim::Yaw::type == Settings::AntiAim::Yaw::type_fake || !bFlip))
			angle.y = edge_angle.y;
	}

	if (Settings::AntiAim::Pitch::enabled)
	{
		int pitch_aa_type = Settings::AntiAim::Pitch::type;

		if (pitch_aa_type == STATIC_UP)
			angle.x = -89.0f;
		else if (pitch_aa_type == STATIC_DOWN)
			angle.x = 89.0f;
		else if (pitch_aa_type == DANCE)
		{
			pDance += 15.0f;

			if (pDance > 100)
				pDance = 0.0f;
			else if (pDance > 50.f)
				angle.x = 330.f;
			else if (pDance < 50.f)
				angle.x = 30.f;
		}
		else if (pitch_aa_type == FRONT)
			angle.x = 0.0f;
#ifdef UNTRUSTED_SETTINGS
		else if (pitch_aa_type == STATIC_UP_FAKE)
		{
			angle.x = bFlip ? 89.0f : -89.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (pitch_aa_type == STATIC_DOWN_FAKE)
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
