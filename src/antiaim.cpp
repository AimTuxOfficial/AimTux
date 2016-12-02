#include "antiaim.h"

bool Settings::AntiAim::enabled_Y = false;
bool Settings::AntiAim::enabled_X = false;
AntiAimType_Y Settings::AntiAim::type_Y = SPIN_FAST;
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
	static float fYaw = 0.0f;
	static float fYaw2 = 0.0f;
	static float rYaw = 0.0f;
	static float pDance = 0.0f;

	bFlip = !bFlip;

	bool aa_edge = false;

	if (Settings::AntiAim::enabled_Y)
	{
		if (Settings::AntiAim::type_Y == SPIN_FAST || Settings::AntiAim::type_Y == SPIN_SLOW)
		{
			fYaw += Settings::AntiAim::type_Y == SPIN_FAST ? 40.0f : 5.0f;

			if (fYaw > 180.0f)
				fYaw -= 360.0f;

			angle.y = fYaw;
		}
		else if (Settings::AntiAim::type_Y == JITTER)
		{
			angle.y = bFlip ? 270.0f : 90.0f;
		}
		else if (Settings::AntiAim::type_Y == SIDE)
		{
			if (bFlip)
				angle.y += 90.0f;
			else
				angle.y -= 90.0f;
		}
		else if (Settings::AntiAim::type_Y == BACKWARDS)
		{
			angle.y -= 180.0f;
		}
		else if (Settings::AntiAim::type_Y == FAKE_BACKWARDS_JITTER)
  		{
			fYaw += 10.0f;

			if (fYaw > 100.0f)
				fYaw = 0.0f;
			else if (fYaw > 50.0f)
				fYaw2 = 210.0f;
			else if (fYaw < 50.0f)
				fYaw2 = 150.0f;

			angle.y = bFlip ? fYaw2 : 180.0f;
  			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SPIN_SLOW_FAKE)
		{
			fYaw += 5.0f;

			if (fYaw > 180)
				fYaw -= 360.0f;

			angle.y = bFlip ? fYaw : 180.f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SPIN_FAST_FAKE)
		{
			fYaw += 40.0f;

			if (fYaw > 180)
				fYaw -= 360.0f;

			angle.y = bFlip ? fYaw : 180.f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == STATIC_FAKE)
		{
			fYaw += 5.0f;

			if (fYaw > 100)
				fYaw = 0.0f;
			else if (fYaw < 50.0f)
				rYaw = 150.f;
			else if (fYaw > 100)
				rYaw = 210.f;

			angle.y = bFlip ? 0.0f : rYaw;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == STATIC_FAKE_FOLLOW)
		{
			if (bFlip)
			{
				fYaw += 5.0f;
				if (fYaw > 100)
				{
				fYaw = 0.0f;
				}
				else if (fYaw < 50.0f)
				{
				angle.y = 150.0f;
				}
				else if (fYaw > 50.0f)
				{
					angle.y = 210.0f;
				}
			}
			else
			{
				angle.y -= 180.0f;
			}
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == BACKWARDS_FAKE)
		{
			angle.y -= bFlip ? 0.0f : (edging_head ? edge_angle.y : 180.0f);
			CreateMove::SendPacket = bFlip;

			aa_edge = bFlip && edging_head;
		}
		else if (Settings::AntiAim::type_Y == FORWARDS_FAKE)
		{
			angle.y -= bFlip ? 180.0f : (edging_head ? edge_angle.y : 0.0f);
			CreateMove::SendPacket = bFlip;

			aa_edge = bFlip && edging_head;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FAKE_RIGHT)
		{
			angle.y -= bFlip ? 90.0f : -90.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FAKE_LEFT)
		{
			angle.y -= bFlip ? -90.0f : 90.0f;
			CreateMove::SendPacket = bFlip;
		}
		else if (Settings::AntiAim::type_Y == SIDE_FLIP_FAKE)
		{
			static bool bFlip_0;

			if (bFlip)
			{
				bFlip_0 = !bFlip_0;
				angle.y -= bFlip_0 ? 90.0f : -90.0f;
			}
			else
			{
				angle.y -= 180.0f;
			}

			CreateMove::SendPacket = bFlip;
		}
	}

	if (edging_head && !aa_edge)
		angle.y = edge_angle.y;

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
		else if (Settings::AntiAim::type_X == STATIC_FRONT)
		{
			angle.x = 0.0f;
		}
		else if (Settings::AntiAim::type_X == DANCE)
		{
			pDance += 15.0f;

			if (pDance > 100)
				pDance = 0.0f;
			else if (pDance > 50.0f)
				angle.x = 330.f;
			else if (pDance < 50.0f)
				angle.x = 30.f;
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
