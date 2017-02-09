#include "jumpthrow.h"

bool inAttackState = false;
bool Settings::JumpThrow::enabled = false;
ButtonCode_t Settings::JumpThrow::key = ButtonCode_t::KEY_T;

void JumpThrow::CreateMove(CUserCmd* cmd)
{
	if(!Settings::JumpThrow::enabled)
		return;

	C_BasePlayer* localplayer = (C_BasePlayer*) entityList->GetClientEntity(engine->GetLocalPlayer());

	if(!localplayer)
		return;

	C_BaseCombatWeapon* activeWeapon = (C_BaseCombatWeapon*) entityList->GetClientEntityFromHandle(localplayer->GetActiveWeapon());
	ItemDefinitionIndex itemDefinitionIndex = *activeWeapon->GetItemDefinitionIndex();

	if (!(itemDefinitionIndex == ItemDefinitionIndex::WEAPON_FLASHBANG || itemDefinitionIndex == ItemDefinitionIndex::WEAPON_HEGRENADE || itemDefinitionIndex == ItemDefinitionIndex::WEAPON_SMOKEGRENADE || itemDefinitionIndex == ItemDefinitionIndex::WEAPON_MOLOTOV || itemDefinitionIndex == ItemDefinitionIndex::WEAPON_DECOY || itemDefinitionIndex == ItemDefinitionIndex::WEAPON_INCGRENADE))
		return;

	if (localplayer->GetMoveType() == MOVETYPE_LADDER || localplayer->GetMoveType() == MOVETYPE_NOCLIP)
		return;

	if (!inputSystem->IsButtonDown(Settings::JumpThrow::key) && !inAttackState)
		return;

	if (!inputSystem->IsButtonDown(Settings::JumpThrow::key) && inAttackState)
	{
		cmd->buttons |= IN_JUMP;
		inAttackState = false;
		return;
	}
	cmd->buttons |= IN_ATTACK;
	inAttackState = true;
}
