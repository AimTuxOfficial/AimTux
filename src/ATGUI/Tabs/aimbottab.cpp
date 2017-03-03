#include "../atgui.h"

static ItemDefinitionIndex currentWeapon = ItemDefinitionIndex::INVALID;
static bool enabled = false;
static bool silent = false;
static bool friendly = false;
static Bone bone = Bone::BONE_HEAD;
static ButtonCode_t aimkey = ButtonCode_t::MOUSE_MIDDLE;
static bool aimkeyOnly = false;
static bool smoothEnabled = false;
static float smoothValue = 0.5f;
static SmoothType smoothType = SmoothType::SLOW_END;
static bool smoothSaltEnabled = false;
static float smoothSaltMultiplier = 0.0f;
static bool errorMarginEnabled = false;
static float errorMarginValue = 0.0f;
static bool autoAimEnabled = false;
static float autoAimValue = 180.0f;
static bool aimStepEnabled = false;
static float aimStepValue = 25.0f;
static bool rcsEnabled = false;
static bool rcsAlwaysOn = false;
static float rcsAmountX = 2.0f;
static float rcsAmountY = 2.0f;
static bool autoPistolEnabled = false;
static bool autoShootEnabled = false;
static bool autoScopeEnabled = false;
static bool noShootEnabled = false;
static bool ignoreJumpEnabled = false;
static bool smokeCheck = false;
static bool flashCheck = false;
static bool autoWallEnabled = false;
static float autoWallValue = 10.0f;
static bool autoWallBones[] = { true, false, false, false, false, false };
static bool autoAimRealDistance = false;
static bool autoSlow = false;
static bool predEnabled = false;
static float autoSlowMinDamage = 5.0f;

void UI::ReloadWeaponSettings()
{
	ItemDefinitionIndex index = ItemDefinitionIndex::INVALID;
	if (Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
		index = currentWeapon;

	enabled = Settings::Aimbot::weapons.at(index).enabled;
	silent = Settings::Aimbot::weapons.at(index).silent;
	friendly = Settings::Aimbot::weapons.at(index).friendly;
	bone = Settings::Aimbot::weapons.at(index).bone;
	aimkey = Settings::Aimbot::weapons.at(index).aimkey;
	aimkeyOnly = Settings::Aimbot::weapons.at(index).aimkeyOnly;
	smoothEnabled = Settings::Aimbot::weapons.at(index).smoothEnabled;
	smoothValue = Settings::Aimbot::weapons.at(index).smoothAmount;
	smoothType = Settings::Aimbot::weapons.at(index).smoothType;
	smoothSaltEnabled = Settings::Aimbot::weapons.at(index).smoothSaltEnabled;
	smoothSaltMultiplier = Settings::Aimbot::weapons.at(index).smoothSaltMultiplier;
	errorMarginEnabled = Settings::Aimbot::weapons.at(index).errorMarginEnabled;
	errorMarginValue = Settings::Aimbot::weapons.at(index).errorMarginValue;
	autoAimEnabled = Settings::Aimbot::weapons.at(index).autoAimEnabled;
	autoAimValue = Settings::Aimbot::weapons.at(index).autoAimFov;
	aimStepEnabled = Settings::Aimbot::weapons.at(index).aimStepEnabled;
	aimStepValue = Settings::Aimbot::weapons.at(index).aimStepValue;
	rcsEnabled = Settings::Aimbot::weapons.at(index).rcsEnabled;
	rcsAlwaysOn = Settings::Aimbot::weapons.at(index).rcsAlwaysOn;
	rcsAmountX = Settings::Aimbot::weapons.at(index).rcsAmountX;
	rcsAmountY = Settings::Aimbot::weapons.at(index).rcsAmountY;
	autoPistolEnabled = Settings::Aimbot::weapons.at(index).autoPistolEnabled;
	autoShootEnabled = Settings::Aimbot::weapons.at(index).autoShootEnabled;
	autoScopeEnabled = Settings::Aimbot::weapons.at(index).autoScopeEnabled;
	noShootEnabled = Settings::Aimbot::weapons.at(index).noShootEnabled;
	ignoreJumpEnabled = Settings::Aimbot::weapons.at(index).ignoreJumpEnabled;
	smokeCheck = Settings::Aimbot::weapons.at(index).smokeCheck;
	flashCheck = Settings::Aimbot::weapons.at(index).flashCheck;
	autoWallEnabled = Settings::Aimbot::weapons.at(index).autoWallEnabled;
	autoWallValue = Settings::Aimbot::weapons.at(index).autoWallValue;
	autoAimRealDistance = Settings::Aimbot::weapons.at(index).autoAimRealDistance;
	autoSlow = Settings::Aimbot::weapons.at(index).autoSlow;
	predEnabled = Settings::Aimbot::weapons.at(index).predEnabled;
	autoSlowMinDamage = Settings::Aimbot::weapons.at(index).autoSlowMinDamage;

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		autoWallBones[bone] = Settings::Aimbot::weapons.at(index).autoWallBones[bone];
}

void UI::UpdateWeaponSettings()
{
	if (Settings::Aimbot::weapons.find(currentWeapon) == Settings::Aimbot::weapons.end())
		Settings::Aimbot::weapons[currentWeapon] = AimbotWeapon_t();

	AimbotWeapon_t settings = {
			enabled, silent, friendly, bone, aimkey, aimkeyOnly,
			smoothEnabled, smoothValue, smoothType, smoothSaltEnabled, smoothSaltMultiplier,
			errorMarginEnabled, errorMarginValue,
			autoAimEnabled, autoAimValue, aimStepEnabled, aimStepValue,
			rcsEnabled, rcsAlwaysOn, rcsAmountX, rcsAmountY,
			autoPistolEnabled, autoShootEnabled, autoScopeEnabled,
			noShootEnabled, ignoreJumpEnabled, smokeCheck, flashCheck, autoWallEnabled, autoWallValue, autoAimRealDistance, autoSlow, autoSlowMinDamage, predEnabled
	};

	for (int bone = (int) Hitbox::HITBOX_HEAD; bone <= (int) Hitbox::HITBOX_ARMS; bone++)
		settings.autoWallBones[bone] = autoWallBones[bone];

	Settings::Aimbot::weapons.at(currentWeapon) = settings;

	if (Settings::Aimbot::weapons.at(currentWeapon) == Settings::Aimbot::weapons.at(ItemDefinitionIndex::INVALID) &&
		currentWeapon != ItemDefinitionIndex::INVALID)
	{
		Settings::Aimbot::weapons.erase(currentWeapon);
		UI::ReloadWeaponSettings();
	}
}

void Aimbot::RenderTab()
{
	const char* targets[] = { "PELVIS", "", "", "HIP", "LOWER SPINE", "MIDDLE SPINE", "UPPER SPINE", "NECK", "HEAD" };
	const char* smoothTypes[] = { "Slow Near End", "Constant Speed", "Fast Near End" };
	static char filterWeapons[32];

	if (ImGui::Checkbox("Enabled", &enabled))
		UI::UpdateWeaponSettings();
	ImGui::Separator();

	ImGui::Columns(3, NULL, true);
	{
		ImGui::SetColumnOffset(1, 200);
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##FILTERWEAPONS", filterWeapons, IM_ARRAYSIZE(filterWeapons));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##GUNS", ImVec2(-1, -1));
		for (auto it : ItemDefinitionIndexMap)
		{
			bool isDefault = (int) it.first < 0;
			if (!isDefault && !Util::Contains(Util::ToLower(std::string(filterWeapons)), Util::ToLower(Util::Items::GetItemDisplayName(it.first).c_str())))
				continue;

			if (Util::Items::IsKnife(it.first) || Util::Items::IsGlove(it.first) || Util::Items::IsUtility(it.first))
				continue;

			const bool item_selected = ((int) it.first == (int) currentWeapon);
			ImGui::PushID((int) it.first);
			std::string formattedName;
			char changeIndicator = ' ';
			bool isChanged = Settings::Aimbot::weapons.find(it.first) != Settings::Aimbot::weapons.end();
			if (!isDefault && isChanged)
				changeIndicator = '*';
			formattedName = changeIndicator + (isDefault ? Util::Items::GetItemDisplayName(it.first).c_str() : Util::Items::GetItemDisplayName(it.first));
			if (ImGui::Selectable(formattedName.c_str(), item_selected))
			{
				currentWeapon = it.first;
				UI::ReloadWeaponSettings();
			}
			ImGui::PopID();
		}
		ImGui::ListBoxFooter();
	}
	ImGui::NextColumn();
	{
		ImGui::SetColumnOffset(2, ImGui::GetWindowWidth() / 2 + 75);
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Friendly", &friendly))
					UI::UpdateWeaponSettings();
				SetTooltip("Whether to target friendlies");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##AIMTARGET", (int*)& bone, targets, IM_ARRAYSIZE(targets)))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Accuracy");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Auto Aim", &autoAimEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Locks onto enemies within a certain FOV amount");
				if (ImGui::Checkbox("Recoil Control", &rcsEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically controls recoil");
				if (ImGui::Checkbox("Distance-Based FOV", &autoAimRealDistance))
					UI::UpdateWeaponSettings();
				SetTooltip("Takes perspective into account when calculating FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AA", &autoAimValue, 0, 180))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
				if (ImGui::Button("RCS Settings", ImVec2(-1, 0)))
					ImGui::OpenPopup("optionRCSAmount");
				ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("optionRCSAmount"))
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Checkbox("RCS Always on", &rcsAlwaysOn))
						UI::UpdateWeaponSettings();
					SetTooltip("Whether Recoil Control always controls recoil (even when not aimbotting)");
					if (ImGui::SliderFloat("##RCSX", &rcsAmountX, 0, 2, "X: %0.3f"))
						UI::UpdateWeaponSettings();
					if (ImGui::SliderFloat("##RCSY", &rcsAmountY, 0, 2, "Y: %0.3f"))
						UI::UpdateWeaponSettings();
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Humanizing");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Smoothing", &smoothEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Smoothing reduces the aimbot \"snap\". 0 for full snap. 1 for full smoothing");
				if (ImGui::Checkbox("Smooth Salting", &smoothSaltEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Breaks the smoothing into smaller steps, high smooth + low salt is slightly stuttery");
				if (ImGui::Checkbox("Error Margin", &errorMarginEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Adds a margin of error to the aim, it will be obvious what it does when using it");
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##SMOOTHTYPE", (int*)& smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##SMOOTH", &smoothValue, 0, 1))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##SALT", &smoothSaltMultiplier, 0, smoothValue))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##ERROR", &errorMarginValue, 0, 2))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("COL2", ImVec2(0, 0), true);
		{
			ImGui::Text("Aimkey Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled", &aimkeyOnly))
					UI::UpdateWeaponSettings();
				SetTooltip("Enabling this means it you need to press a specific key to aimlock");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&aimkey);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Casual / DM Only");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Aim Step", &aimStepEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Stops you getting VAC auth kicked in Casual / DM");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##STEP", &aimStepValue, 0, 45))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				switch (currentWeapon)
				{
					case ItemDefinitionIndex::INVALID:
					case ItemDefinitionIndex::WEAPON_DEAGLE:
					case ItemDefinitionIndex::WEAPON_ELITE:
					case ItemDefinitionIndex::WEAPON_FIVESEVEN:
					case ItemDefinitionIndex::WEAPON_GLOCK:
					case ItemDefinitionIndex::WEAPON_TEC9:
					case ItemDefinitionIndex::WEAPON_HKP2000:
					case ItemDefinitionIndex::WEAPON_USP_SILENCER:
					case ItemDefinitionIndex::WEAPON_P250:
					case ItemDefinitionIndex::WEAPON_CZ75A:
					case ItemDefinitionIndex::WEAPON_REVOLVER:
						if (ImGui::Checkbox("Auto Pistol", &autoPistolEnabled))
							UI::UpdateWeaponSettings();
						SetTooltip("Automatically shoots the pistol when holding fire");
						break;
					default:
						break;
				}

				if (ImGui::Checkbox("Auto Shoot", &autoShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically shoots when locking to an enemy");
				if (ImGui::Checkbox("Silent Aim", &silent))
					UI::UpdateWeaponSettings();
				SetTooltip("Prevents the camera from locking to an enemy, doesn't work for demos");
				if (ImGui::Checkbox("Smoke Check", &smokeCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("Ignore players that are blocked by smoke");
				if (ImGui::Checkbox("Prediction", &predEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Use velocity prediction");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("No Shoot", &noShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Stops you shooting when locking to an enemy");
				if (ImGui::Checkbox("Auto Scope", &autoScopeEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Automatically scopes weapons that have them");
				if (ImGui::Checkbox("Ignore Jump", &ignoreJumpEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Prevents you from aimbotting while jumping");
				if (ImGui::Checkbox("Flash Check", &flashCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("Disable aimbot while flashed");
			}

			if (autoWallEnabled)
			{
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("AutoSlow");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					if (ImGui::Checkbox("Enabled##AUTOSLOW", &autoSlow))
						UI::UpdateWeaponSettings();
					SetTooltip("Automatically slows your movement speed when an enemy is shootable");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::SliderFloat("##AUTOSLOWMINDAMAGE", &autoSlowMinDamage, 0, 100, "Min Damage: %f"))
						UI::UpdateWeaponSettings();
					ImGui::PopItemWidth();
				}
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled##AUTOWALL", &autoWallEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("Shoots enemy through a wall if it does X amount of damage");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AUTOWALLDMG", &autoWallValue, 0, 100, "Min Damage: %f"))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("AutoWall Target");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Head", &autoWallBones[(int) Hitbox::HITBOX_HEAD]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on head");
				if (ImGui::Checkbox("Neck", &autoWallBones[(int) Hitbox::HITBOX_NECK]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on neck");
				if (ImGui::Checkbox("Pelvis", &autoWallBones[(int) Hitbox::HITBOX_PELVIS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on pelvis");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("Spine", &autoWallBones[(int) Hitbox::HITBOX_SPINE]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on spine");
				if (ImGui::Checkbox("Legs", &autoWallBones[(int) Hitbox::HITBOX_LEGS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on legs");
				if (ImGui::Checkbox("Arms", &autoWallBones[(int) Hitbox::HITBOX_ARMS]))
					UI::UpdateWeaponSettings();
				SetTooltip("Trigger on arms");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			if (currentWeapon > ItemDefinitionIndex::INVALID && Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
			{
				if (ImGui::Button("Clear Weapon Settings", ImVec2(-1, 0)))
				{
					Settings::Aimbot::weapons.erase(currentWeapon);
					UI::ReloadWeaponSettings();
				}
			}
			ImGui::EndChild();
		}
	}
}