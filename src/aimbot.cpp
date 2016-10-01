#include "aimbot.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = true;
float Settings::Aimbot::fov = 180.0f;
bool Settings::Aimbot::AutoAim::enabled = true;
bool Settings::Aimbot::AutoShoot::enabled = true;
bool Settings::Aimbot::RCS::enabled = true;
bool Settings::Aimbot::AutoCrouch::enabled = false;
bool Settings::Aimbot::AutoStop::enabled = false;

void Aimbot::CheckAngles (QAngle& angle)
{
	if (angle[0] > 89	) angle[0] = 89;
	if (angle[0] < -89	) angle[0] = -89;
	if (angle[1] > 180	) angle[1] -= 360;
	if (angle[1] < -180	) angle[1] += 360;
	angle[2] = 0;
}

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
			|| entity->GetLifeState() != 0
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localplayer->GetTeam())
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

C_BaseEntity* GetClosestVisibleEnemy (CUserCmd* cmd)
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
			|| entity->GetLifeState() != 0
			|| entity->GetHealth() <= 0
			|| entity->GetTeam() == localplayer->GetTeam()
			|| !Entity::IsVisible (localplayer, entity, 6))
			continue;

		float e_dist = localplayer->GetVecOrigin().DistToSqr (entity->GetVecOrigin());

		Vector e_vecHead = GetBone (entity, 6);
		Vector p_vecHead = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();
		float fov = Math::GetFov(cmd->viewangles, Math::CalcAngle(p_vecHead, e_vecHead));

		if (e_dist < dist && fov <= Settings::Aimbot::fov)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}

void Aimbot::RCS (QAngle& angle)
{
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	angle -= localplayer->GetAimPunchAngle() * 2.f;
}

void Aimbot::CorrectMovement (QAngle vOldAngles, CUserCmd* pCmd, float fOldForward, float fOldSidemove)
{
	//side/forward move correction
	float deltaView = pCmd->viewangles.y - vOldAngles.y;
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

bool isPistol(C_BaseCombatWeapon* weapon)
{
	switch (*weapon->GetItemDefinitionIndex())
	{
		case WEAPON_DEAGLE:
			return true;
		case WEAPON_ELITE:
			return true;
		case WEAPON_FIVESEVEN:
			return true;
		case WEAPON_GLOCK:
			return true;
		case WEAPON_TEC9:
			return true;
		case WEAPON_HKP2000:
			return true;
		case WEAPON_USP_SILENCER:
			return true;
		case WEAPON_P250:
			return true;
		case WEAPON_CZ75A:
			return true;
		case WEAPON_REVOLVER:
			return true;
		default:
			return false;
	}
}

bool isAutomatic(C_BaseCombatWeapon* weapon)
{
	switch (*weapon->GetItemDefinitionIndex())
	{
		case WEAPON_AK47:
			return true;
		case WEAPON_AUG:
			return true;
		case WEAPON_FAMAS:
			return true;
		case WEAPON_GALILAR:
			return true;
		case WEAPON_M249:
			return true;
		case WEAPON_M4A1:
			return true;
		case WEAPON_M4A1_SILENCER:
			return true;
		case WEAPON_MAC10:
			return true;
		case WEAPON_P90:
			return true;
		case WEAPON_UMP45:
			return true;
		case WEAPON_BIZON:
			return true;
		case WEAPON_NEGEV:
			return true;
		case WEAPON_MP7:
			return true;
		case WEAPON_MP9:
			return true;
		case WEAPON_SG556:
			return true;
		default:
			return false;
	}
}

bool isKnife(C_BaseCombatWeapon* weapon) {
	switch (*weapon->GetItemDefinitionIndex()) {
		case WEAPON_KNIFE:
			return true;
		case WEAPON_KNIFE_T:
			return true;
		case WEAPON_KNIFE_GUT:
			return true;
		case WEAPON_KNIFE_FLIP:
			return true;
		case WEAPON_KNIFE_BAYONET:
			return true;
		case WEAPON_KNIFE_M9_BAYONET:
			return true;
		case WEAPON_KNIFE_KARAMBIT:
			return true;
		case WEAPON_KNIFE_TACTICAL:
			return true;
		case WEAPON_KNIFE_BUTTERFLY:
			return true;
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return true;
		case WEAPON_KNIFE_FALCHION:
			return true;
		case WEAPON_KNIFE_PUSH:
			return true;
		default:
			return false;
	}
}

void Aimbot::CreateMove (CUserCmd* cmd)
{
	if (!Settings::Aimbot::enabled)
		return;

	QAngle oldAngle = cmd->viewangles;
	float oldForward = cmd->forwardmove;
	float oldSideMove = cmd->sidemove;
	
	QAngle angle = cmd->viewangles;
	
	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));
	
	C_BaseEntity* entity = GetClosestVisibleEnemy (cmd);
	
	if (entity)
	{
		if (Settings::Aimbot::AutoAim::enabled &&
			(Settings::Aimbot::AutoShoot::enabled || cmd->buttons & IN_ATTACK))
		{
			Vector e_vecHead = GetBone (entity, 6);
			Vector p_vecHead = localplayer->GetVecOrigin() + localplayer->GetVecViewOffset();
			
			CalculateAngle (p_vecHead, e_vecHead, angle);
		}
		
		if (Settings::Aimbot::AutoShoot::enabled)
		{
			C_BaseViewModel* viewmodel = reinterpret_cast<C_BaseViewModel*>(entitylist->GetClientEntity(localplayer->GetViewModel() & 0xFFF));
			C_BaseCombatWeapon* active_weapon = reinterpret_cast<C_BaseCombatWeapon*>(entitylist->GetClientEntity(viewmodel->GetWeapon() & 0xFFF));
			
			if (active_weapon && !isKnife(active_weapon) && active_weapon->GetAmmo() > 0)
			{
				if (!isAutomatic(active_weapon))
				{
					static bool fire;

					if (fire)
					{
						if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
							cmd->buttons &= ~IN_ATTACK2;
						else
							cmd->buttons &= ~IN_ATTACK;

						fire = false;
					}
					else
					{
						if (*active_weapon->GetItemDefinitionIndex() == WEAPON_REVOLVER)
							cmd->buttons |= IN_ATTACK2;
						else
							cmd->buttons |= IN_ATTACK;

						fire = true;
					}
				}
				else
				{
					cmd->buttons |= IN_ATTACK;
				}
			}
		}
		
		if (Settings::Aimbot::AutoCrouch::enabled)
		{
			cmd->buttons |= IN_DUCK;
		}

		if (Settings::Aimbot::AutoStop::enabled)
		{
			oldForward = 0;
			oldSideMove = 0;
			cmd->upmove = 0;
		}
	}

	if (Settings::Aimbot::RCS::enabled)
	{
		RCS (angle);
	}

	// Check the angle to make sure it's invalid
	Aimbot::CheckAngles (angle);
	
	cmd->viewangles = angle;

	Aimbot::CorrectMovement (oldAngle, cmd, oldForward, oldSideMove);
}



