#include "aimbot.h"
#include "autowall.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
bool Settings::Aimbot::silent = false;
bool Settings::Aimbot::friendly = false;
float Settings::Aimbot::fov = 180.0f;
float Settings::Aimbot::errorMargin = 0.0F;
unsigned int Settings::Aimbot::bone = BONE_HEAD;
ButtonCode_t Settings::Aimbot::aimkey = ButtonCode_t::MOUSE_MIDDLE;
bool Settings::Aimbot::Smooth::enabled = false;
float Settings::Aimbot::Smooth::value = 1.0f;
float Settings::Aimbot::Smooth::max = 15.0f;
bool Settings::Aimbot::AutoAim::enabled = false;
bool Settings::Aimbot::AutoWall::enabled = false;
float Settings::Aimbot::AutoWall::value = 10.0f;
bool Settings::Aimbot::AimStep::enabled = false;
float Settings::Aimbot::AimStep::value = 25.0f;
bool Settings::Aimbot::AutoShoot::enabled = false;
bool Settings::Aimbot::AutoShoot::autoscope = false;
bool Settings::Aimbot::RCS::enabled = false;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::AutoStop::enabled = false;
bool Aimbot::AimStepInProgress = false;

QAngle AimStepLastAngle;
QAngle RCSLastPunch;

static void ApplyErrorToAngle(QAngle* angles, float margin)
{
    QAngle error;
    error.Random(-1.0F, 1.0F);
    error *= margin;

    angles->operator+=(error);
}

void CalculateAngle(Vector& src, Vector& dst, QAngle& angles)
{
	// Angle deltas
	double delta[3] = { (src[0] - dst[0]), (src[1] - dst[1]), (src[2] - dst[2]) };

	// Hypotenuse
	double hyp = sqrt(delta[0] * delta[0] + delta[1] * delta[1]);

	angles[0] = (float) (atan(delta[2] / hyp) * 57.295779513082f);
	angles[1] = (float) (atan(delta[1] / delta[0]) * 57.295779513082f);

	if (delta[0] >= 0.0)
		angles[1] += 180.0f;

	Math::NormalizeAngles(angles);
}

C_BaseEntity* GetClosestEnemy(CUserCmd* cmd, bool visible)
{
	C_BasePlayer* localplayer = (C_BasePlayer*)entitylist->GetClientEntity(engine->GetLocalPlayer());
	C_BaseEntity* closestEntity = NULL;
	float dist = 10000000.0f;

	visible = visible && !Settings::Aimbot::AutoWall::enabled;

	if (!localplayer)
		return NULL;

	for (int i = 0; i < 64; ++i)
	{
		C_BaseEntity* entity = entitylist->GetClientEntity(i);

		if (!entity
			|| entity == (C_BaseEntity*)localplayer
			|| entity->GetDormant()
			|| entity->GetLifeState() != LIFE_ALIVE
			|| entity->GetHealth() <= 0)
			continue;

		if (!Settings::Aimbot::friendly && entity->GetTeam() == localplayer->GetTeam())
			continue;

		float e_dist = localplayer->GetVecOrigin().DistToSqr(entity->GetVecOrigin());
		Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
		Vector p_vecHead = localplayer->GetEyePosition();
		float fov = Math::GetFov(cmd->viewangles, Math::CalcAngle(p_vecHead, e_vecHead));

		if (Settings::Aimbot::AutoWall::enabled && Autowall::GetDamage(e_vecHead) < Settings::Aimbot::AutoWall::value)
				continue;

		if (visible && !Entity::IsVisible(entity, Settings::Aimbot::bone))
				continue;

		if (e_dist < dist && fov <= Settings::Aimbot::fov)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}

void Aimbot::RCS(QAngle& angle, bool hasTarget)
{
	C_BasePlayer *localplayer = reinterpret_cast<C_BasePlayer *>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	QAngle CurrentPunch = localplayer->GetAimPunchAngle();

	if (Settings::Aimbot::silent || hasTarget)
	{
		angle -= CurrentPunch * 2.f;
		RCSLastPunch = CurrentPunch;
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

	float yaw = std::min((float)abs(target_yaw - view_yaw), 360.f - abs(target_yaw - view_yaw));

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

	C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntityFromHandle(localplayer->GetActiveWeapon()));
	if (active_weapon->isGrenade() || active_weapon->isKnife())
		return;

	C_BaseEntity* entity = GetClosestEnemy(cmd, true);

	if (entity)
	{
		if (Settings::Aimbot::AutoAim::enabled &&
			(Settings::Aimbot::AutoShoot::enabled || cmd->buttons & IN_ATTACK || input->IsButtonDown(Settings::Aimbot::aimkey)))
		{
			Vector e_vecHead = entity->GetBonePosition(Settings::Aimbot::bone);
			Vector p_vecHead = localplayer->GetEyePosition();

			if (!Aimbot::AimStepInProgress)
				AimStepLastAngle = cmd->viewangles;

			CalculateAngle(p_vecHead, e_vecHead, angle);
            ApplyErrorToAngle(&angle, Settings::Aimbot::errorMargin);

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
			if (!active_weapon->isKnife() && active_weapon->GetAmmo() > 0)
			{
				float nextPrimaryAttack = active_weapon->GetNextPrimaryAttack();
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
					if (Settings::Aimbot::AutoShoot::autoscope && active_weapon->CanScope() && !localplayer->IsScoped())
						cmd->buttons |= IN_ATTACK2;
					else if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
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
		Aimbot::RCS(angle, Settings::Aimbot::AutoAim::enabled && entity != NULL);

	Math::NormalizeAngles(angle);

	cmd->viewangles = angle;

	Math::CorrectMovement(oldAngle, cmd, oldForward, oldSideMove);
}



