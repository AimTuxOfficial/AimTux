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
	const char* targets[] = { "ТАЗ (жопа)", "", "", "БЕДРА", "НИЖНИЙ ОТДЕЛ ПОЗВОНОЧНИКА", "СЕРЕДИНА ПОЗВОНОЧНИКА", "ВЕРХНЕГО ОТДЕЛА ПОЗВОНОЧНИКА", "ШЕЯ", "ГОЛОВА" };
	const char* smoothTypes[] = { "ЧЕМ БЛИЖЕ К ЦЕЛИ ТЕМ МЕДЛЕННЕЙ", "С ОДНОЙ СКОРОСТЬЮ", "ЧЕМ БЛИЖЕ К ЦЕЛИ ТЕМ БЫСТРЕЕ" };
	static char filterWeapons[32];

	if (ImGui::Checkbox("АКТИВАЦИЯ", &enabled))
		UI::UpdateWeaponSettings();
	ImGui::Separator();

	ImGui::Columns(3, NULL, true);
	{
		ImGui::SetColumnOffset(1, 200);
		ImGui::PushItemWidth(-1);
		ImGui::InputText("##ФИЛЬТРЫ", filterWeapons, IM_ARRAYSIZE(filterWeapons));
		ImGui::PopItemWidth();
		ImGui::ListBoxHeader("##ПУШКИ", ImVec2(-1, -1));
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
			ImGui::Text("ЦЕЛЬ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("ДРУЖЕЛЮБНЫЙ", &friendly))
					UI::UpdateWeaponSettings();
				SetTooltip("НАВОДИТЬСЯ НА СВОИХ (ДЛЯ НЕКОТОРЫХ СЕРВЕРОВ DM");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##ПРИЦЕЛ НВ ЦЕЛЬ", (int*)& bone, targets, IM_ARRAYSIZE(targets)))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("ТОЧНОСТЬ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("АВТОЦЕЛЬ", &autoAimEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("РАДИУС ЗАХВАТА ПРИЦЕЛОМ ЦЕЛИ");
				if (ImGui::Checkbox("КОНТРОЛЬ РАЗБРОСА (ТОЛЬКО В РАДИУСЕ ЗАХВАТА)", &rcsEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("АВТОМАТИЧЕСКИЙ КОНТРОЛЬ РАЗБРОСА (ТОЛЬКО В РАДИУСЕ FOV");
				if (ImGui::Checkbox("ДИНАМИЧЕСКИЙ РАДИУС ЗАХВАТА", &autoAimRealDistance))
					UI::UpdateWeaponSettings();
				SetTooltip("ДИНАМИЧЕСКИЙ РАДИУС ЗАХВАТА ЦЕЛИ (ЧЕМ БЛИЖЕ К ЦЕЛИ ТЕМ БОЛЬШЕ РАДИУС");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AA", &autoAimValue, 0, 180))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
				if (ImGui::Button("RCS НАСТРОЙКИ", ImVec2(-1, 0)))
					ImGui::OpenPopup("optionRCSAmount");
				ImGui::SetNextWindowSize(ImVec2(200, 100), ImGuiSetCond_Always);
				if (ImGui::BeginPopup("optionRCSAmount"))
				{
					ImGui::PushItemWidth(-1);
					if (ImGui::Checkbox("RCS ВКЛЮЧЕНИЕ", &rcsAlwaysOn))
						UI::UpdateWeaponSettings();
					SetTooltip("НЕЗАВИСИМО ОТ ТОГО ЦЕЛЬ В РАДИУСЕ НАВОДКИ ИЛИ НЕТ, КОНТРОЛИРУТ РАЗБРОС (ДАЖЕ ЕСЛИ ОТКЛЮЧЕНА НАВОДКА)");
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
			ImGui::Text("ГУМАНИЗАЦИЯ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("СГЛАЖИВАНИЕ", &smoothEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("СКОРОСТЬ НАВОДКИ НА ЦЕЛЬ \"snap\". 0 ДЛЯ БЫСТРОЙ НАВОДКИ. 1 ДЛЯ ДОЛГОЙ НАВОДКИ");
				if (ImGui::Checkbox("СГЛАЖИВАНИЕ ПО ИНТЕРВАЛАМ", &smoothSaltEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("РАЗРЫВАНИЕ ИНТЕРВАЛОВ НАВОДКИ (ЗАВИСИТ ОТ ТИПА ЗГЛАЖИВАНИЯ НАВОДКИ)");
				if (ImGui::Checkbox("ПОГРЕШНОСТИ НАВЕДЕНИЯ", &errorMarginEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("ДОБАВЛЯЕТ ПОГРЕШНОСТЬ В НАВИДЕНИЕ (Я ТАК И НЕ ПОНЯЛ ЧТО ИМЕННО ЭТО ДАЕТ)");
				ImGui::PushItemWidth(-1);
				if (ImGui::Combo("##ТИП СГЛАЖИВАНИЯ НАВОДКИ", (int*)& smoothType, smoothTypes, IM_ARRAYSIZE(smoothTypes)))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##ПЛАВНОСТЬ", &smoothValue, 0, 1))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##ИНТЕРВАЛ", &smoothSaltMultiplier, 0, smoothValue))
					UI::UpdateWeaponSettings();
				if (ImGui::SliderFloat("##ОШИБКИ", &errorMarginValue, 0, 2))
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
			ImGui::Text("АИМ НА КНОПКУ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("ВКЛЮЧЕН", &aimkeyOnly))
					UI::UpdateWeaponSettings();
				SetTooltip("ЗАХВАТ ЦЕЛИ ПРОИЗВОДИТЬСЯ ТОЛЬКО ПРИ НАЖАТИИ И УДЕРЖАНИИ НАЗНАЧЕННОЙ КЛАВИШИ");
			}
			ImGui::NextColumn();
			{
				UI::KeyBindButton(&aimkey);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("ПОВСЕДНЕВНОЕ И ДМ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("НАВОДКА НА КЛАВИШУ", &aimStepEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("ПОМОГАЕТ ПРЕДОТВРАТИТЬ ПОЛУЧЕНИЕ ВАК БАНА(ПАТРУЛЕМ) В МАТЧАХ И В DM (Я ТАК И НЕ ПОНЯЛ ЧТО ЭТО ТОЧНО)");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##ШАГ", &aimStepValue, 0, 45))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("ОСТАЛЬНОЕ");
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
						if (ImGui::Checkbox("АВТОМАТИЧЕСКИЙ ПИСТОЛЕТ", &autoPistolEnabled))
							UI::UpdateWeaponSettings();
						SetTooltip("АВТОМАТИЧЕСКАЯ СТРЕЛЬБА ИЗ ПИСТОЛЕТА ПРИ УДЕРЖАНИИ КЛАВИШИ ОГОНЬ (ОБЫЧНО ЭТО mause1");
						break;
					default:
						break;
				}

				if (ImGui::Checkbox("АВТОМАТИЧЕСКИЙ ОГОНЬ", &autoShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("АВТОМАТИЧЕСКИЙ ОГОНЬ ПРИ НАХОЖДЕНИЯ ПРОТИВНИКА В РАДИУСЕ НАВОДКИ (FOV)");
				if (ImGui::Checkbox("БЕЗПАЛЕВНЫЙ АИМ", &silent))
					UI::UpdateWeaponSettings();
				SetTooltip("ПРЕДОТВРАЩАЕТ БЛОКИРОВКУ КАМЕРЫ НА ВРАГЕ");
				if (ImGui::Checkbox("ПРОВЕРЯТЬ ДЫМ", &smokeCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("ИГНОРИРОВАТЬ ИГРОКОВ ЗА ДЫМОМ");
				if (ImGui::Checkbox("ПРОГНОЗИРОВАНИЕ", &predEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("ПРОГНОЗИРОВАТЬ ПЕРЕМЕЩЕНИЯ ПРОТИВНИКА");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("НЕ СТРЕЛЯТЬ", &noShootEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("ПРИ НАВОДКЕ НА ПРОТИВНИКА СТРЕЛЬБА ОСТАНАВЛИВАЕТЬСЯ (Я НЕ ПОНЯЛ ТОЧНО КАК ЭТО РАБОТАЕТ)");
				if (ImGui::Checkbox("АВТОЗУМ", &autoScopeEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("АВТОМАТИЧЕСКИ ЗУМИТЬСЯ НА ПРОТИВНИКЕ");
				if (ImGui::Checkbox("ИГНОРИРОВАТЬ ПРЫЖКИ", &ignoreJumpEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("КОГДА ВЫ ПРЫГАЕТЕ АИМ НЕ СРАБАТЫВАЕТ");
				if (ImGui::Checkbox("СЛЕПЫМ НЕ НАВОДИТЬСЯ", &flashCheck))
					UI::UpdateWeaponSettings();
				SetTooltip("ОТКЛЮЧЕНИЯ АИМА КОГДА ВЫ ОСЛЕПЛЕНЫ");
			}

			if (autoWallEnabled)
			{
				ImGui::Columns(1);
				ImGui::Separator();
				ImGui::Text("АВТОЗАМЕДЛЕНИЕ");
				ImGui::Separator();
				ImGui::Columns(2, NULL, true);
				{
					if (ImGui::Checkbox("Enabled##AUTOSLOW", &autoSlow))
						UI::UpdateWeaponSettings();
					SetTooltip("АВТОМАТИЧЕСКИ ЗАМЕДЛЯЕТ ВАС КОГДА В ВАС СТРЕЛЯЕТЕ (НЕ УВЕРЕН)");
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
			ImGui::Text("СТРЕЛЯТЬ ЧЕРЕЗ СТЕНЫ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("Enabled##AUTOWALL", &autoWallEnabled))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА СКВОЗЬ СТЕНУ, НО ТОЛЬКО ЕСЛИ ЕСТЬ ВЕРОЯТНОСТЬ НАНЕСТИ Х ПОВРЕЖДЕНИЙ");
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				if (ImGui::SliderFloat("##AUTOWALLDMG", &autoWallValue, 0, 100, "МИНИМАЛЬНЫЙ УРОН: %f"))
					UI::UpdateWeaponSettings();
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text("АВТОМАТИЧЕСКАЯ СТРЕЛЬБА СКВОЗЬ СТЕНЫ");
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				if (ImGui::Checkbox("ГОЛОВА", &autoWallBones[(int) Hitbox::HITBOX_HEAD]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В ГОЛОВУ");
				if (ImGui::Checkbox("ШЕЯ", &autoWallBones[(int) Hitbox::HITBOX_NECK]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В ШЕЮ");
				if (ImGui::Checkbox("ТАЗ", &autoWallBones[(int) Hitbox::HITBOX_PELVIS]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В ТАЗ");
			}
			ImGui::NextColumn();
			{
				if (ImGui::Checkbox("СПИНА", &autoWallBones[(int) Hitbox::HITBOX_SPINE]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В СПИНУ");
				if (ImGui::Checkbox("НОГИ", &autoWallBones[(int) Hitbox::HITBOX_LEGS]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В НОГИ");
				if (ImGui::Checkbox("ОРУЖИЕ", &autoWallBones[(int) Hitbox::HITBOX_ARMS]))
					UI::UpdateWeaponSettings();
				SetTooltip("СТРЕЛЬБА В ОРУЖИЕ (РУКИ)");
			}
			ImGui::Columns(1);
			ImGui::Separator();
			if (currentWeapon > ItemDefinitionIndex::INVALID && Settings::Aimbot::weapons.find(currentWeapon) != Settings::Aimbot::weapons.end())
			{
				if (ImGui::Button("СБРОСИТЬ НАСТРОЙКИ НА СТОКОВЫЕ", ImVec2(-1, 0)))
				{
					Settings::Aimbot::weapons.erase(currentWeapon);
					UI::ReloadWeaponSettings();
				}
			}
			ImGui::EndChild();
		}
	}
}