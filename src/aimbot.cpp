#include "aimbot.h"

// Default aimbot settings
bool Settings::Aimbot::enabled = false;

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

CBaseEntity* GetClosestEnemy ()
{
	CBaseEntity* pLocal = entitylist->GetClientEntity(engine->GetLocalPlayer());
	CBaseEntity* closestEntity = NULL;
	float dist = 10000000.0f;

	if (!pLocal)
		return NULL;

	for(int i = 0; i < 64; ++i)
	{
		CBaseEntity* entity = entitylist->GetClientEntity(i);
		C_BasePlayer* player = reinterpret_cast<C_BasePlayer*>(entity);

		if (!entity || entity == pLocal ||
				player->GetDormant() || player->GetLifeState() != LIFE_ALIVE || player->GetHealth() <= 0)
			continue;

		C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

		if (entity->m_iTeamNum == localplayer->m_iTeamNum)
			continue;

		float e_dist = localplayer->m_vecOrigin.DistToSqr (entity->m_vecOrigin);

		if (e_dist < dist)
		{
			closestEntity = entity;
			dist = e_dist;
		}
	}

	return closestEntity;
}


void Aimbot::Calculate ()
{
	CBaseEntity* entity = GetClosestEnemy ();

	if (entity == NULL)
		return;

	C_BasePlayer* localplayer = reinterpret_cast<C_BasePlayer*>(entitylist->GetClientEntity(engine->GetLocalPlayer()));

	Vector e_vecOrigin = entity->m_vecOrigin;
	Vector p_vecOrigin = localplayer->m_vecOrigin;

	QAngle angle;
	CalculateAngle (p_vecOrigin, e_vecOrigin, angle);

	engine->SetViewAngles (angle);
}