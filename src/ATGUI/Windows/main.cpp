#include "main.h"

bool Main::showWindow = false;

static char nickname[127] = "";

namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
					 static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values, int height_in_items = -1)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
					   static_cast<void*>(&values), values.size(), height_in_items);
	}
}

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

	AimbotWeapon_t settings = {enabled, silent, friendly, bone, aimkey, aimkeyOnly,
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

void AimbotTab()
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

			if (it.first >= ItemDefinitionIndex::WEAPON_KNIFE_BAYONET ||
				it.first == ItemDefinitionIndex::WEAPON_KNIFE ||
				it.first == ItemDefinitionIndex::WEAPON_KNIFE_T ||
				(it.first >= ItemDefinitionIndex::WEAPON_FLASHBANG && it.first <= ItemDefinitionIndex::WEAPON_C4))
				continue;

			const bool item_selected = ((int)it.first == (int) currentWeapon);
			ImGui::PushID((int)it.first);
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
				if (ImGui::Button("Clear Weapon Settings", ImVec2(-1, 0)))
				{
					Settings::Aimbot::weapons.erase(currentWeapon);
					UI::ReloadWeaponSettings();
				}
			ImGui::EndChild();
		}
	}
}

void TriggerbotTab()
{
	ImGui::Checkbox("Enabled", &Settings::Triggerbot::enabled);
	ImGui::Separator();
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("TRIG1", ImVec2(0, 0), true);
		{
			ImGui::Text("Keybind");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Trigger Key");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::Triggerbot::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Delay");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::Triggerbot::Delay::enabled);
				SetTooltip("Adds a delay to the Triggerbot");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("TRIG2", ImVec2(0, 0), true);
		{
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::Triggerbot::Filters::enemies);
				SetTooltip("Trigger on enemies");
				ImGui::Checkbox("Walls", &Settings::Triggerbot::Filters::walls);
				SetTooltip("Trigger through walls");
				ImGui::Checkbox("Head", &Settings::Triggerbot::Filters::head);
				SetTooltip("Trigger on head");
				ImGui::Checkbox("Chest", &Settings::Triggerbot::Filters::chest);
				SetTooltip("Trigger on chest");
				ImGui::Checkbox("Legs", &Settings::Triggerbot::Filters::legs);
				SetTooltip("Trigger on legs");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::Triggerbot::Filters::allies);
				SetTooltip("Trigger on allies");
				ImGui::Checkbox("Smoke check", &Settings::Triggerbot::Filters::smokeCheck);
				SetTooltip("Don't shoot through smokes");
				ImGui::Checkbox("Flash check", &Settings::Triggerbot::Filters::flashCheck);
				SetTooltip("Don't shoot while flashed");
				ImGui::Checkbox("Stomach", &Settings::Triggerbot::Filters::stomach);
				SetTooltip("Trigger on stomach");
				ImGui::Checkbox("Arms", &Settings::Triggerbot::Filters::arms);
				SetTooltip("Trigger on arms");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
}

void VisualsTab()
{
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Rainbow", "Wireframe", "None" };

	ImGui::Checkbox("Enabled", &Settings::ESP::enabled);
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("COL1", ImVec2(0, 0), true);
		{
			ImGui::Text("ESP");
			ImGui::BeginChild("ESP", ImVec2(0, 0), true);
			ImGui::Text("Type");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Outline Box", &Settings::ESP::Boxes::enabled);
				SetTooltip("Outline players with a box");
				ImGui::Checkbox("Chams", &Settings::ESP::Chams::enabled);
				SetTooltip("Change players' model texture");
				ImGui::Checkbox("Health", &Settings::ESP::Bars::enabled);
				SetTooltip("Show a players health with a bar");
				ImGui::Checkbox("Tracers", &Settings::ESP::Tracers::enabled);
				SetTooltip("Draws a line to each player");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Bar Color");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Team Color");
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Checkbox("Bullet Tracers", &Settings::ESP::BulletTracers::enabled);
				SetTooltip("Adds a line showing where a player is aiming");
				ImGui::Checkbox("Head Dot", &Settings::ESP::HeadDot::enabled);
				SetTooltip("Adds a Dot on the Head of a player");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##BOXTYPE", (int*)& Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
				ImGui::Combo("##CHAMSTYPE", (int*)& Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
				ImGui::Combo("##BARTYPE", (int*)& Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
				ImGui::Combo("##TRACERTYPE", (int*)& Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
				ImGui::Combo("##BARCOLTYPE", (int*)& Settings::ESP::Bars::colorType, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
				ImGui::Combo("##TEAMCOLTYPE", (int*)& Settings::ESP::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Skeleton", &Settings::ESP::Skeleton::enabled);
				SetTooltip("Show a players skeleton");
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##HDOTSIZE", &Settings::ESP::HeadDot::size, 1.f, 10.f, "Size: %0.3f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Filter");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enemies", &Settings::ESP::Filters::enemies);
				SetTooltip("Show enemies");
				ImGui::Checkbox("Chickens", &Settings::ESP::Filters::chickens);
				SetTooltip("Show chickens");
				ImGui::Checkbox("LocalPlayer", &Settings::ESP::Filters::localplayer);
				SetTooltip("Show localplayer");
				ImGui::Checkbox("Legit Mode", &Settings::ESP::Filters::legit);
				SetTooltip("Hide enemies behind walls");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Allies", &Settings::ESP::Filters::allies);
				SetTooltip("Show team mates");
				ImGui::Checkbox("Fish", &Settings::ESP::Filters::fishes);
				SetTooltip("Show fish");
				ImGui::Checkbox("Smoke Check", &Settings::ESP::Filters::smokeCheck);
				SetTooltip("Mark players behind smokes as invisible");
				ImGui::Checkbox("Visiblity Check", &Settings::ESP::Filters::visibilityCheck);
				SetTooltip("Change color of outlined box based on whether you see them");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Player Information");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Clan", &Settings::ESP::Info::clan);
				SetTooltip("Show clan");
				ImGui::Checkbox("Rank", &Settings::ESP::Info::rank);
				SetTooltip("Show rank");
				ImGui::PushID(1);
				ImGui::Checkbox("Health", &Settings::ESP::Info::health);
				SetTooltip("Show health");
				ImGui::PopID();
				ImGui::Checkbox("Scoped", &Settings::ESP::Info::scoped);
				SetTooltip("Show whether they are scoped");
				ImGui::Checkbox("Flashed", &Settings::ESP::Info::flashed);
				SetTooltip("Show whether they are flashed");
				ImGui::Checkbox("Defuse Kit", &Settings::ESP::Info::hasDefuser);
				SetTooltip("Show whether they have a defuse kit");
				ImGui::Checkbox("Grabbing Hostage", &Settings::ESP::Info::grabbingHostage);
				SetTooltip("Show whether they are grabbing a hostage");
				ImGui::Checkbox("Location", &Settings::ESP::Info::location);
				SetTooltip("Show location");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Name", &Settings::ESP::Info::name);
				SetTooltip("Show name");
				ImGui::Checkbox("Steam ID", &Settings::ESP::Info::steamId);
				SetTooltip("Show Steam ID");
				ImGui::Checkbox("Weapon", &Settings::ESP::Info::weapon);
				SetTooltip("Show held weapon");
				ImGui::Checkbox("Reloading", &Settings::ESP::Info::reloading);
				SetTooltip("Show whether they are reloading");
				ImGui::Checkbox("Planting", &Settings::ESP::Info::planting);
				SetTooltip("Show whether they are planting");
				ImGui::Checkbox("Defusing", &Settings::ESP::Info::defusing);
				SetTooltip("Show whether they are defusing");
				ImGui::Checkbox("Rescuing Hostage", &Settings::ESP::Info::rescuing);
				SetTooltip("Show whether they are rescuing a hostage");
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("World");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Weapons", &Settings::ESP::Filters::weapons);
				SetTooltip("Show weapons on floor");
				ImGui::Checkbox("Throwables", &Settings::ESP::Filters::throwables);
				SetTooltip("Show throwables");
				ImGui::Checkbox("Entity Glow", &Settings::ESP::Glow::enabled);
				SetTooltip("Show a glow around entities");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Bomb", &Settings::ESP::Filters::bomb);
				SetTooltip("Show bomb when planted");
				ImGui::Checkbox("Defuse Kits", &Settings::ESP::Filters::defusers);
				SetTooltip("Show defuse kits on floor");
				ImGui::Checkbox("Hostages", &Settings::ESP::Filters::hostages);
				SetTooltip("Show hostages");
			}
			ImGui::Columns(1);
			ImGui::EndChild();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		ImGui::BeginChild("Chams", ImVec2(0, 0), true);
		{
			ImGui::Text("Crosshair");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Recoil Crosshair", &Settings::Recoilcrosshair::enabled);
				SetTooltip("Show a crosshair based on recoil");
				ImGui::Checkbox("FOV Circle", &Settings::ESP::FOVCrosshair::enabled);
				SetTooltip("Show circle around aimbot FOV");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Only When Shooting", &Settings::Recoilcrosshair::showOnlyWhenShooting);
				SetTooltip("Only show recoil crosshair when shooting");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other Visual Settings");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Arms", &Settings::ESP::Chams::Arms::enabled);
				SetTooltip("Apply chams to arms");
				ImGui::Checkbox("Dlights", &Settings::Dlights::enabled);
				SetTooltip("Adds a light source to players");
				ImGui::Checkbox("No Flash", &Settings::Noflash::enabled);
				SetTooltip("Hide flashbang effect");
				ImGui::Checkbox("Show Footsteps", &Settings::ESP::Sounds::enabled);
				SetTooltip("Shows you footsteps in 3D space");
				ImGui::Checkbox("No View Punch", &Settings::View::NoViewPunch::enabled);
				SetTooltip("Disables view punch when shooting");
				ImGui::Checkbox("Weapons", &Settings::ESP::Chams::Weapon::enabled);
				SetTooltip("Apply chams to weapons");
				ImGui::Checkbox("No Sky", &Settings::NoSky::enabled);
				SetTooltip("Allows for the skybox to be colored or disabled");
				ImGui::Checkbox("No Smoke", &Settings::NoSmoke::enabled);
				SetTooltip("Disables smoke rendering");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##ARMSTYPE", (int*)& Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				ImGui::SliderFloat("##DLIGHTRADIUS", &Settings::Dlights::radius, 0, 1000, "Radius: %0.f");
				ImGui::SliderFloat("##NOFLASHAMOUNT", &Settings::Noflash::value, 0, 255, "Amount: %0.f");
				ImGui::SliderInt("##SOUNDSTIME", &Settings::ESP::Sounds::time, 250, 5000, "Timeout: %0.f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("No Aim Punch", &Settings::View::NoAimPunch::enabled);
				SetTooltip("Disables aim punch when shooting");
				ImGui::Checkbox("ASUS Walls", &Settings::ASUSWalls::enabled);
				SetTooltip("Makes wall textures transparent");
				ImGui::Checkbox("No Scope Border", &Settings::NoScopeBorder::enabled);
				SetTooltip("Disables black scope silhouette");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Radar");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Radar", &Settings::Radar::enabled);
				SetTooltip("Shows players on the custom radar");
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##RADARTEAMCOLTYPE", (int*)& Settings::Radar::team_color_type, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox("Enemies", &Settings::Radar::enemies);
				ImGui::Checkbox("Bomb", &Settings::Radar::bomb);
				ImGui::Checkbox("Legit", &Settings::Radar::legit);
				ImGui::Checkbox("In-game Radar", &Settings::Radar::InGame::enabled);
				SetTooltip("Shows players on the in-game radar");

			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##RADARZOOM", &Settings::Radar::zoom, 0.f, 100.f, "Zoom: %0.f");
				ImGui::SliderFloat("##RADARICONSSCALE", &Settings::Radar::iconsScale, 2, 16, "Icons Scale: %0.1f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Allies", &Settings::Radar::allies);
				ImGui::Checkbox("Defuser", &Settings::Radar::defuser);
				ImGui::Checkbox("Visibility Check", &Settings::Radar::visibilityCheck);
				ImGui::Checkbox("Smoke Check", &Settings::Radar::smokeCheck);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text("Hitmarkers");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Hitmarkers", &Settings::ESP::Hitmarker::enabled);
				SetTooltip("Notify when you hit another player");

				ImGui::Checkbox("Enemies##HITMARKERS", &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox("Allies##HITMARKERS", &Settings::ESP::Hitmarker::allies);
				ImGui::Checkbox("Damage##HITMARKERS", &Settings::ESP::Hitmarker::Damage::enabled);
				SetTooltip("Show dealt damage next to the hitmarker");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##HITMARKERDUR", &Settings::ESP::Hitmarker::duration, 250, 3000, "Timeout: %0.f");
				ImGui::SliderInt("##HITMARKERSIZE", &Settings::ESP::Hitmarker::size, 1, 32, "Size: %0.f");
				ImGui::SliderInt("##HITMARKERGAP", &Settings::ESP::Hitmarker::innerGap, 1, 16, "Gap: %0.f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}

void HvHTab()
{
	const char* yTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", // safe
			"LISP", "LISP SIDE", "LISP JITTER", "ANGEL BACKWARDS", "ANGEL INVERSE", "ANGEL SPIN" // untrusted
	};

	const char* xTypes[] = {
			"UP", "DOWN", "DANCE", "FRONT", // safe
			"FAKE UP", "FAKE DOWN", "LISP DOWN", "ANGEL DOWN", "ANGEL UP" // untrusted
	};

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("HVH1", ImVec2(0, 0), true);
		{
			ImGui::Text("AntiAim");
			ImGui::BeginChild("##ANTIAIM", ImVec2(0, 0), true);
			{
				ImGui::Checkbox("Yaw", &Settings::AntiAim::Yaw::enabled);
				SetTooltip("Enables Yaw AntiAim");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Yaw Fake");
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Yaw Actual");
					ImGui::Checkbox("Anti Resolver", &Settings::AntiAim::Yaw::antiResolver);
					SetTooltip("Simple resolver prevention");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##YFAKETYPE", (int*)& Settings::AntiAim::Yaw::typeFake, yTypes, IM_ARRAYSIZE(yTypes)))
					{
						if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::typeFake >= AntiAimType_Y::LISP)
						{
							Settings::AntiAim::Yaw::typeFake = AntiAimType_Y::SPIN_SLOW;
							ImGui::OpenPopup("Error###UNTRUSTED_AA");
						}
					}

					if (ImGui::Combo("##YACTUALTYPE", (int*)& Settings::AntiAim::Yaw::type, yTypes, IM_ARRAYSIZE(yTypes)))
					{
						if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Yaw::type >= AntiAimType_Y::LISP)
						{
							Settings::AntiAim::Yaw::type = AntiAimType_Y::SPIN_SLOW;
							ImGui::OpenPopup("Error###UNTRUSTED_AA");
						}
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Checkbox("Pitch", &Settings::AntiAim::Pitch::enabled);
				SetTooltip("Enables Pitch AntiAim");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
					ImGui::Text("Pitch Actual");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Combo("##XTYPE", (int*)& Settings::AntiAim::Pitch::type, xTypes, IM_ARRAYSIZE(xTypes)))
					{
						if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
						{
							Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
							ImGui::OpenPopup("Error###UNTRUSTED_AA");
						}
					}
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Disable");
				ImGui::Separator();
				ImGui::Checkbox("Knife", &Settings::AntiAim::AutoDisable::knifeHeld);
				SetTooltip("Stops your antiaim while you have your knife out.");
				ImGui::Checkbox("No Enemy", &Settings::AntiAim::AutoDisable::noEnemy);
				SetTooltip("Stops your antiaim when there are no enemies visible.");

				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("Edging");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					ImGui::Checkbox("Enabled", &Settings::AntiAim::HeadEdge::enabled);
					SetTooltip("Aims your head into the closest wall");
				}
				ImGui::NextColumn();
				{
					ImGui::PushItemWidth(-1);
					ImGui::SliderFloat("##EDGEDISTANCE", &Settings::AntiAim::HeadEdge::distance, 10, 30, "Distance: %0.f");
					ImGui::PopItemWidth();
				}
				ImGui::Columns(1);
				ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
				if (ImGui::BeginPopupModal("Error###UNTRUSTED_AA"))
				{
					ImGui::Text("You cannot use this antiaim type on a VALVE server.");

					ImGui::Checkbox("This is not a VALVE server", &ValveDSCheck::forceUT);

					if (ImGui::Button("OK"))
						ImGui::CloseCurrentPopup();

					ImGui::EndPopup();
				}
				ImGui::PopStyleVar();

				ImGui::EndChild();
			}
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("HVH2", ImVec2(0, 0), true);
		{
			ImGui::Text("Resolver");
			ImGui::Separator();
			ImGui::Checkbox("Resolve All", &Settings::Resolver::resolveAll);
			SetTooltip("Resolves all players on the server");
			ImGui::Separator();
			ImGui::Text("Movement");
			ImGui::Checkbox("Auto Crouch", &Settings::Aimbot::AutoCrouch::enabled);
			SetTooltip("Auto crouch when an enemy is in sight");
			ImGui::EndChild();
		}
	}
}

void MiscTab()
{
	const char* strafeTypes[] = { "Forwards", "Backwards", "Left", "Right", "Rage" };
	const char* animationTypes[] = { "Static", "Marquee", "Words", "Letters" };
	const char* spammerTypes[] = { "None", "Normal", "Positions" };
	const char* teams[] = { "Allies", "Enemies", "Both" };

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild("Child1", ImVec2(0, 0), true);
		{
			ImGui::Text("Movement");
			ImGui::Separator();

			ImGui::Checkbox("Bunny Hop", &Settings::BHop::enabled);
			SetTooltip("Auto bunny hop");
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Edge Jump", &Settings::EdgeJump::enabled);
				SetTooltip("Jumps off the edges");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&Settings::EdgeJump::key);
			}
			ImGui::Columns(1);

			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Auto Strafe", &Settings::AutoStrafe::enabled);
				SetTooltip("Auto strafe when bunny hopping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo("##STRAFETYPE", (int*)& Settings::AutoStrafe::type, strafeTypes, IM_ARRAYSIZE(strafeTypes));
				ImGui::PopItemWidth();
			}

			if (Settings::AutoStrafe::type == AutostrafeType::AS_RAGE)
			{
				ImGui::Checkbox("Silent", &Settings::AutoStrafe::silent);
				SetTooltip("Strafes won't be visible for spectators");
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Spammer");
			ImGui::Separator();

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Checkbox("Kill Messages", &Settings::Spammer::KillSpammer::enabled);
				SetTooltip("Spams a kill message when killing an enemy");
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM1", &Settings::Spammer::KillSpammer::sayTeam);
				SetTooltip("Only show kill message in team chat");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Button("Options###KILL"))
					ImGui::OpenPopup("options_kill");

				ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("options_kill"))
				{
					static int killSpammerMessageCurrent = -1;
					static char killSpammerMessageBuf[126];

					ImGui::PushItemWidth(445);
					ImGui::InputText("###SPAMMERMESSAGE", killSpammerMessageBuf, IM_ARRAYSIZE(killSpammerMessageBuf));
					ImGui::PopItemWidth();
					ImGui::SameLine();

					if (ImGui::Button("Add"))
					{
						if (strlen(killSpammerMessageBuf) > 0)
							Settings::Spammer::KillSpammer::messages.push_back(std::string(killSpammerMessageBuf));

						strcpy(killSpammerMessageBuf, "");
					}
					ImGui::SameLine();

					if (ImGui::Button("Remove"))
						if (killSpammerMessageCurrent > -1 && (int) Settings::Spammer::KillSpammer::messages.size() > killSpammerMessageCurrent)
							Settings::Spammer::KillSpammer::messages.erase(Settings::Spammer::KillSpammer::messages.begin() + killSpammerMessageCurrent);

					ImGui::PushItemWidth(550);
					ImGui::ListBox("", &killSpammerMessageCurrent, Settings::Spammer::KillSpammer::messages, 10);
					ImGui::PopItemWidth();

					ImGui::EndPopup();
				}
			}

			ImGui::Columns(1);
			ImGui::Checkbox("Radio Commands", &Settings::Spammer::RadioSpammer::enabled);

			ImGui::Columns(3, NULL, true);
			{
				ImGui::Combo("###SPAMMERYPE", (int*)&Settings::Spammer::type, spammerTypes, IM_ARRAYSIZE(spammerTypes));
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox("Team Chat###SAY_TEAM2", &Settings::Spammer::say_team);
				SetTooltip("Only spam messages in team chat");
			}
			ImGui::NextColumn();
			{
				if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::Button("Options###SPAMMER"))
					ImGui::OpenPopup("options_spammer");

				if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
					ImGui::SetNextWindowSize(ImVec2(565, 268), ImGuiSetCond_Always);
				else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
					ImGui::SetNextWindowSize(ImVec2(200, 240), ImGuiSetCond_Always);

				if (Settings::Spammer::type != SpammerType::SPAMMER_NONE && ImGui::BeginPopup("options_spammer"))
				{
					if (Settings::Spammer::type == SpammerType::SPAMMER_NORMAL)
					{
						static int spammerMessageCurrent = -1;
						static char spammerMessageBuf[126];

						ImGui::PushItemWidth(445);
						ImGui::InputText("###SPAMMERMESSAGE", spammerMessageBuf, IM_ARRAYSIZE(spammerMessageBuf));
						ImGui::PopItemWidth();
						ImGui::SameLine();

						if (ImGui::Button("Add"))
						{
							if (strlen(spammerMessageBuf) > 0)
								Settings::Spammer::NormalSpammer::messages.push_back(std::string(spammerMessageBuf));

							strcpy(spammerMessageBuf, "");
						}
						ImGui::SameLine();

						if (ImGui::Button("Remove"))
							if (spammerMessageCurrent > -1 && (int) Settings::Spammer::NormalSpammer::messages.size() > spammerMessageCurrent)
								Settings::Spammer::NormalSpammer::messages.erase(Settings::Spammer::NormalSpammer::messages.begin() + spammerMessageCurrent);

						ImGui::PushItemWidth(550);
						ImGui::ListBox("", &spammerMessageCurrent, Settings::Spammer::NormalSpammer::messages, 10);
						ImGui::PopItemWidth();
					}
					else if (Settings::Spammer::type == SpammerType::SPAMMER_POSITIONS)
					{
						ImGui::PushItemWidth(185);
						ImGui::Combo("###POSITIONSTEAM", &Settings::Spammer::PositionSpammer::team, teams, IM_ARRAYSIZE(teams));
						ImGui::PopItemWidth();
						ImGui::Separator();
						ImGui::Checkbox("Show Name", &Settings::Spammer::PositionSpammer::showName);
						ImGui::Checkbox("Show Weapon", &Settings::Spammer::PositionSpammer::showWeapon);
						ImGui::Checkbox("Show Rank", &Settings::Spammer::PositionSpammer::showRank);
						ImGui::Checkbox("Show Wins", &Settings::Spammer::PositionSpammer::showWins);
						ImGui::Checkbox("Show Health", &Settings::Spammer::PositionSpammer::showHealth);
						ImGui::Checkbox("Show Money", &Settings::Spammer::PositionSpammer::showMoney);
						ImGui::Checkbox("Show Last Place", &Settings::Spammer::PositionSpammer::showLastplace);
					}

					ImGui::EndPopup();
				}
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("FOV");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("FOV", &Settings::FOVChanger::enabled);
				SetTooltip("Change camera FOV");
				ImGui::Checkbox("Viewmodel FOV", &Settings::FOVChanger::viewmodelEnabled);
				SetTooltip("Change viewmodel FOV");
				ImGui::Checkbox("Ignore Scope", &Settings::FOVChanger::ignoreScope);
				SetTooltip("Disable FOV Changer while scoping");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##FOVAMOUNT", &Settings::FOVChanger::value, 0, 180);
				ImGui::SliderFloat("##MODELFOVAMOUNT", &Settings::FOVChanger::viewmodelValue, 0, 360);
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Third Person");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Enabled", &Settings::ThirdPerson::enabled);
				SetTooltip("Switches from first-person perspective to third-person perspective.");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat("##TPCAMOFFSET", &Settings::ThirdPerson::distance, 0.f, 500.f, "Camera Offset: %0.f");
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::EndChild();
		}
	}
	ImGui::NextColumn();
	{
		ImGui::BeginChild("Child2", ImVec2(0, 0), true);
		{
			ImGui::Text("Clantag");
			ImGui::Separator();
			ImGui::Checkbox("Enabled", &Settings::ClanTagChanger::enabled);
			SetTooltip("Display a custom clantag");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::InputText("##CLANTAG", Settings::ClanTagChanger::value, 30))
					ClanTagChanger::UpdateClanTagCallback();
				ImGui::PopItemWidth();

				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text("Animation Speed");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##ANIMATIONTYPE", (int*)& Settings::ClanTagChanger::type, animationTypes, IM_ARRAYSIZE(animationTypes)))
					ClanTagChanger::UpdateClanTagCallback();
				if (ImGui::SliderInt("##ANIMATIONSPEED", &Settings::ClanTagChanger::animationSpeed, 0, 2000))
					ClanTagChanger::UpdateClanTagCallback();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Nickname");
			ImGui::Separator();

			ImGui::InputText("##NICKNAME", nickname, 127);

			ImGui::SameLine();
			if (ImGui::Button("Set Nickname", ImVec2(-1, 0)))
				NameChanger::SetName(std::string(nickname).c_str());

			if (ImGui::Button("Glitch Name"))
				NameChanger::SetName("\n\xAD\xAD\xAD");
			SetTooltip("Allows you to change your name an infinite amount of times and doesn't show in server message");
			ImGui::SameLine();
			if (ImGui::Button("No Name"))
			{
				NameChanger::changes = 0;
				NameChanger::type = NameChanger::NC_Type::NC_NORMAL;
			}

			ImGui::SameLine();
			if (ImGui::Button("Rainbow Name"))
				NameChanger::InitColorChange(NameChanger::NC_Type::NC_RAINBOW);

			ImGui::SameLine();
			if (ImGui::Button("Colorize Name", ImVec2(-1, 0)))
				ImGui::OpenPopup("optionColorizeName");
			ImGui::SetNextWindowSize(ImVec2(150, 300), ImGuiSetCond_Always);
			if (ImGui::BeginPopup("optionColorizeName"))
			{
				ImGui::PushItemWidth(-1);
				for (auto& it : NameChanger::colors)
				{
					if (ImGui::Button(it.second, ImVec2(-1, 0)))
						NameChanger::InitColorChange(NameChanger::NC_Type::NC_SOLID, it.first);
				}
				ImGui::PopItemWidth();

				ImGui::EndPopup();
			}
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Name Stealer", &Settings::NameStealer::enabled))
					NameStealer::entityId = -1;
			}
			ImGui::NextColumn();
			{
				ImGui::Combo("", &Settings::NameStealer::team, teams, IM_ARRAYSIZE(teams));
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("Other");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox("Fake Lag", &Settings::FakeLag::enabled);
				SetTooltip("Chokes packets so it appears you're lagging");
				ImGui::Checkbox("Adaptive Fake Lag", &Settings::FakeLag::adaptive);
				SetTooltip("Chokes packets based on velocity (minimum choked is fakelag value)");
				ImGui::Checkbox("Auto Accept", &Settings::AutoAccept::enabled);
				SetTooltip("Auto accept games when in MM queue");
				ImGui::Checkbox("Auto Defuse", &Settings::AutoDefuse::enabled);
				SetTooltip("Will automatically defuse the bomb with 0.5 seconds remaining - starts at 5.5 seconds until explosion with kit and 10.5 without");
				ImGui::Checkbox("AirStuck", &Settings::Airstuck::enabled);
				SetTooltip("Stops tickrate so you freeze in place");
				ImGui::Checkbox("Autoblock", &Settings::Autoblock::enabled);
				SetTooltip("Allows you to block players from moving forwards by standing in front of them and mirroring their moves - great for griefing");
				if (ImGui::Checkbox("Teleport", &Settings::Teleport::enabled))
				{
					if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::Teleport::enabled)
					{
						Settings::Teleport::enabled = false;
						ImGui::OpenPopup("Error###UNTRUSTED_FEATURE");
					}
				}
				SetTooltip("Teleport to (0, 0) on any map");
				ImGui::Checkbox("Jump Throw", &Settings::JumpThrow::enabled);
				SetTooltip("Hold to prime grenade, release to perform perfect jump throw. Good for executing map smokes.");
				ImGui::Checkbox("Sniper Crosshair", &Settings::SniperCrosshair::enabled);
				SetTooltip("Enables the the crosshair with sniper rifles");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt("##FAKELAGAMOUNT", &Settings::FakeLag::value, 0, 16, "Amount: %0.f");
				ImGui::PopItemWidth();
				ImGui::Checkbox("Show Ranks", &Settings::ShowRanks::enabled);
				SetTooltip("Displays competitive rank of all players in the scoreboard next to their name during a competitive match");
				ImGui::Checkbox("Screenshot Cleaner", &Settings::ScreenshotCleaner::enabled);
				SetTooltip("Prevents AimTux visuals from appearing in screenshots taken");
				UI::KeyBindButton(&Settings::Airstuck::key);
				UI::KeyBindButton(&Settings::Autoblock::key);
				UI::KeyBindButton(&Settings::Teleport::key);
				UI::KeyBindButton(&Settings::JumpThrow::key);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
			if (ImGui::BeginPopupModal("Error###UNTRUSTED_FEATURE"))
			{
				ImGui::Text("You cannot use this feature on a VALVE server.");

				ImGui::Checkbox("This is not a VALVE server", &ValveDSCheck::forceUT);

				if (ImGui::Button("OK"))
					ImGui::CloseCurrentPopup();

				ImGui::EndPopup();
			}
			ImGui::PopStyleVar();

			ImGui::EndChild();
		}
	}
}

void Main::RenderWindow()
{
	if (!Main::showWindow)
		return;

	static int page = 0;
	ImGui::SetNextWindowSize(ImVec2(960, 645), ImGuiSetCond_FirstUseEver);
	if (ImGui::Begin("AimTux", &Main::showWindow, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders))
	{
		const char* tabs[] = {
				"Aimbot",
				"Triggerbot",
				"Visuals",
				"HvH",
				"Misc",
		};

		for (int i = 0; i < IM_ARRAYSIZE(tabs); i++)
		{
			int distance = i == page ? 0 : i > page ? i - page : page - i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = ImVec4(
					Settings::UI::mainColor.Value.x - (distance * 0.035f),
					Settings::UI::mainColor.Value.y - (distance * 0.035f),
					Settings::UI::mainColor.Value.z - (distance * 0.035f),
					Settings::UI::mainColor.Value.w
			);

			if (ImGui::Button(tabs[i], ImVec2(ImGui::GetWindowSize().x / IM_ARRAYSIZE(tabs) - 9, 0)))
				page = i;

			ImGui::GetStyle().Colors[ImGuiCol_Button] = Settings::UI::mainColor;

			if (i < IM_ARRAYSIZE(tabs) - 1)
				ImGui::SameLine();
		}

		ImGui::Separator();

		switch (page)
		{
			case 0:
				AimbotTab();
				break;
			case 1:
				TriggerbotTab();
				break;
			case 2:
				VisualsTab();
				break;
			case 3:
				HvHTab();
				break;
			case 4:
				MiscTab();
				break;
		}
		ImGui::End();
	}
}