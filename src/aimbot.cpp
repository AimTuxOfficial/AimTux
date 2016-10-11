#include "aimbot.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
bool Settings::Aimbot::silent = false;
float Settings::Aimbot::fov = 180.0f;
int Settings::Aimbot::bone = BONE_HEAD;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 1.0f;
float Settings::Aimbot::Smooth::max = 15.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
bool Settings::Aimbot::AimStep::enabled = false;
float Settings::Aimbot::AimStep::value = 25.0f;
bool Settings::Aimbot::AutoShoot::enabled = false;
bool Settings::Aimbot::RCS::enabled = false;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::AutoStop::enabled = false;

QAngle AimStepLastAngle;
QAngle RCSLastPunch;

bool Aimbot::AimStepInProgress = false;

void Aimbot::CheckAngles(QAngle& angle)
{
	if (angle[0] > 89)
		angle[0] = 89;

	if (angle[0] < -89)
		angle[0] = -89;

	if (angle[1] > 180)
		angle[1] -= 360;

	if (angle[1] < -180)
		angle[1] += 360;

	angle[2] = 0;
}

double hyp;

void CalculateAngle(Vector& src, Vector& dst, QAngle& angles)
{
	// Angle deltas
	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };

	// Hypotenuse
	hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	angles[0] = (float) (atan(delta[2]/hyp) * 57.295779513082f);
	angles[1] = (float) (atan(delta[1]/delta[0]) * 57.295779513082f);
	angles[2] = 0.0f;	// <=== NEVER EVER  EVER EVER EVER CHANGE THIS VALUE
						//					... unless you teh VAC ban ...

	if (delta[0] >= 0.0)
		angles[1] += 180.0f;

	// Safeguards
	if (angles[1] > 180)
		angles[1] -= 360;

	if (angles[1] < -180)
		angles[1] += 360;

	if (angles[0] > 89)
		angles[0] = 89;

	if (angles[0] < -89)
		angles[0] = -89;
}

C_BaseEntity* GetClosestEnemy()
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseEntity* closestEntity = NULL;
	float dist = 10000000.0f;

	if (!localplayer)
		return NULL;

	for (int i = 0; i < 64; ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		if (!entity
			|| entity == (C_BaseEntity*)localplayer
			|| entity->GetDormant()
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localplayer->GetTeam())
			continue;

		float e_dist = localplayer->GetVecOrigin().DistToSqr(entity->GetVecOrigin());

		if (e_dist < dist)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}

C_BaseEntity* GetClosestVisibleEnemy(CUserCmd* cmd)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseEntity* closestEntity = NULL;
	float dist = 10000000.0f;

	if (!localplayer)
		return NULL;

	for (int i = 0; i < 64; ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		if (!entity
			|| entity == (C_BaseEntity*)localplayer
			|| entity->GetDormant()
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localplayer->GetTeam()
			|| !Entity::IsVisible(localplayer, entity, Settings::Aimbot::bone))
			continue;

		float e_dist = localplayer->GetVecOrigin().DistToSqr(entity->GetVecOrigin());

		Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
		Vector p_vecHead = localplayer->GetEyePosition();
		float fov = Math::GetFov(cmd->viewangles, Math::CalcAngle(p_vecHead, e_vecHead));

		if (e_dist < dist && fov <= Settings::Aimbot::fov)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}

void Aimbot::RCS(QAngle& angle)
{
	C_BasePlayer *localplayer = reinterpret_cast<C_BasePlayer *>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	QAngle CurrentPunch = localplayer->GetAimPunchAngle();

	if (Settings::Aimbot::silent)
	{
		angle -= CurrentPunch * 2.f;
		return;
	}

	if (localplayer->GetShotsFired() > 1)
	{
		QAngle NewPunch = {CurrentPunch.x - RCSLastPunch.x, CurrentPunch.y - RCSLastPunch.y, 0};

		angle -= NewPunch * 2.f;
		RCSLastPunch = CurrentPunch;
	}
	else
	{
		RCSLastPunch = { 0, 0, 0 };
	}
}

void Aimbot::Smooth(QAngle& angle, CUserCmd* cmd)
{
	QAngle delta = angle - cmd->viewangles;

	float target_yaw = angle.y;
	float view_yaw = cmd->viewangles.y;
	float smooth_factor = 50.f;

	if (angle.y < 0)
		target_yaw = 360.f + angle.y;

	if (cmd->viewangles.y < 0)
		view_yaw = 360.f + cmd->viewangles.y;

	float yaw = std::min((float) abs(target_yaw - view_yaw), 360.f - abs(target_yaw - view_yaw));

	if (cmd->viewangles.y > 90.f && angle.y < -90.f)
	{
		angle.x = cmd->viewangles.x + delta.x / smooth_factor * (Settings::Aimbot::Smooth::max - Settings::Aimbot::Smooth::value);
		angle.y = cmd->viewangles.y + yaw / smooth_factor * (Settings::Aimbot::Smooth::max - Settings::Aimbot::Smooth::value);

		if (angle.y > 180.f)
			angle.y = -360.f + angle.y;

		return;
	}

	if (cmd->viewangles.y < -90.f && angle.y > 90.f)
	{
		angle.x = cmd->viewangles.x + delta.x / smooth_factor * (Settings::Aimbot::Smooth::max - Settings::Aimbot::Smooth::value);
		angle.y = cmd->viewangles.y - yaw / smooth_factor * (Settings::Aimbot::Smooth::max - Settings::Aimbot::Smooth::value);

		if (angle.y < -180.f)
			angle.y = 360.f + angle.y;

		return;
	}

	angle = cmd->viewangles + delta / smooth_factor * (Settings::Aimbot::Smooth::max - Settings::Aimbot::Smooth::value);
}

void Aimbot::CorrectMovement(QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
	//side/forward move correction
	float deltaView;
	float f1;
	float f2;
	
	if (vOldAngles.y < 0.f)
		f1 = 360.0f + vOldAngles.y;
	else
		f1 = vOldAngles.y;
	
	if (pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + pCmd->viewangles.y;
	else
		f2 = pCmd->viewangles.y;
	
	if (f2 < f1)
		deltaView = abs(f2 - f1);
	else
		deltaView = 360.0f - abs(f1 - f2);

	deltaView = 360.0f - deltaView;
	
	pCmd->forwardmove = cos(DEG2RAD(deltaView)) * fOldForward + cos(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
	pCmd->sidemove = sin(DEG2RAD(deltaView)) * fOldForward + sin(DEG2RAD(deltaView + 90.f)) * fOldSidemove;
}

void Aimbot::CreateMove(CUserCmd* cmd)
{
	if (!Settings::Aimbot::enabled)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;
	
	QAngle angle = cmd->viewangles;
	
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

	if (localplayer->GetDormant() || localplayer->GetLifeState() != LIFE_ALIVE || localplayer->GetHealth() == 0)
		return;
	
	C_BaseEntity* entity = GetClosestVisibleEnemy(cmd);
	
	if (entity)
	{
		if (Settings::Aimbot::AutoAim::enabled &&
			(Settings::Aimbot::AutoShoot::enabled || cmd->buttons & IN_ATTACK))
		{
			Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
			Vector p_vecHead = localplayer->GetEyePosition();

			if (!Aimbot::AimStepInProgress)
				AimStepLastAngle = cmd->viewangles;

			CalculateAngle(p_vecHead, e_vecHead, angle);

			float fov = Math::GetFov(AimStepLastAngle, Math::CalcAngle(p_vecHead, e_vecHead));

			Aimbot::AimStepInProgress = (Settings::Aimbot::AimStep::enabled
					&& !Settings::Aimbot::Smooth::enabled
					&& fov > Settings::Aimbot::AimStep::value);

			if (Aimbot::AimStepInProgress)
			{
				QAngle AimStepDelta = AimStepLastAngle - angle;

				if (AimStepDelta.y < 0)
					AimStepLastAngle.y += Settings::Aimbot::AimStep::value;
				else
					AimStepLastAngle.y -= Settings::Aimbot::AimStep::value;

				AimStepLastAngle.x = angle.x;
				angle = AimStepLastAngle;
			}

			if (!Settings::AntiAim::enabled_X && !Settings::AntiAim::enabled_Y && Settings::Aimbot::Smooth::enabled)
				Aimbot::Smooth(angle, cmd);
		}
		
		if (Settings::Aimbot::AutoShoot::enabled && !Aimbot::AimStepInProgress)
		{
			C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon()));

			if (active_weapon && !active_weapon->isKnife() && active_weapon->GetAmmo() > 0)
			{
				float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack ();
				
				float tick = localplayer->GetTickBase() * globalvars->interval_per_tick;
				
				if (nextPrimaryAttack > tick)
				{
					if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
						cmd->buttons &= ~IN_ATTACK2;
					else
						cmd->buttons &= ~IN_ATTACK;
				}
				else
				{
					if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
						cmd->buttons |= IN_ATTACK2;
					else
						cmd->buttons |= IN_ATTACK;
				}
			}
		}
		
		if (Settings::Aimbot::AutoCrouch::enabled)
			cmd->buttons |= IN_DUCK;

		if (Settings::Aimbot::AutoStop::enabled)
		{
			oldForward = 0;
			oldSideMove = 0;
			cmd->upmove = 0;
		}
	}

	if (Settings::Aimbot::RCS::enabled && cmd->buttons & IN_ATTACK)
		Aimbot::RCS(angle);

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles(angle);
	
	cmd->viewangles = angle;

	Aimbot::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}



