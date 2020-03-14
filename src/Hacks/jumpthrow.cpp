#include "jumpthrow.h"

#include "../settings.h"
#include "../interfaces.h"

bool inAttackState = false;

void JumpThrow::CreateMove(CUserCmd* cmd)
{
	if (!Settings::JumpThrow::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());
	if (!localplayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	if (!activeWeapon)
		return;

	if (activeWeapon->GetCSWpnData()->GetWeaponType() != CSWeaponType::WEAPONTYPE_GRENADE){
		inAttackState = false;
		return;
	}

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (!inputSystem->IsButtonDown(Settings::JumpThrow::key) && !inAttackState)
		return;

	if (!inputSystem->IsButtonDown(Settings::JumpThrow::key) && inAttackState)
	{
		cmd->buttons |= IN_JUMP;
		cmd->buttons &= ~IN_ATTACK;
		inAttackState = false;
		return;
	}

	cmd->buttons |= IN_ATTACK;
	inAttackState = true;
}
