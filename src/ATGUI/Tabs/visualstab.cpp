#include "visualstab.h"

void Visuals::RenderTab()
{
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D", "Hitboxes" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Wireframe", "None" };

	const char* SkyBoxes[] = {
			"cs_baggage_skybox_", // 0
			"cs_tibet",
			"embassy",
			"italy",
			"jungle",
			"office",
			"nukeblank",
			"sky_venice",
			"sky_cs15_daylight01_hdr",
			"sky_cs15_daylight02_hdr",
			"sky_cs15_daylight03_hdr",
			"sky_cs15_daylight04_hdr",
			"sky_csgo_cloudy01",
			"sky_csgo_night_flat",
			"sky_csgo_night02",
			"sky_csgo_night02b",
			"sky_day02_05",
			"sky_day02_05_hdr",
			"sky_dust",
			"vertigo",
			"vertigo_hdr",
			"vertigoblue_hdr",
			"vietnam" // 21
	};
	const char *tracerEffectNames[] = {
			"Assault Rifle", // 0
			"Pistol",
			"SMG",
			"Rifle",
			"Kisak Snot",
			"Machine Gun",
			"Shotgun",
			"Kisak Snot Fallback",
			"Kisak Snot Fallback2",
			"Wire1A",
			"Wire2",
			"Wire1B",
			"Original",
			"Backup",
			".50 Cal",
			".50 Cal Glow",
			".50 Cal Low",
			".50 Cal Low Glow", // 17
	};

	ImGui::Columns(2, NULL, true);
	{
		ImGui::Checkbox(XORSTR("Enabled"), &Settings::ESP::enabled);
		ImGui::NextColumn();
		ImGui::Text(XORSTR("Only on Key"));
		UI::KeyBindButton(&Settings::ESP::key);
	}
	ImGui::Separator();

	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild(XORSTR("COL1"), ImVec2(0, 0), true);
		{
			ImGui::Text(XORSTR("ESP"));
			ImGui::BeginChild(XORSTR("ESP"), ImVec2(0, 0), true);
			ImGui::Text(XORSTR("Type"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Outline Box"), &Settings::ESP::Boxes::enabled);
				ImGui::Checkbox(XORSTR("Chams"), &Settings::ESP::Chams::enabled);
				ImGui::Checkbox(XORSTR("Health"), &Settings::ESP::Bars::enabled);
				ImGui::Checkbox(XORSTR("Tracers"), &Settings::ESP::Tracers::enabled);
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text(XORSTR("Bar Color"));
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Text(XORSTR("Team Color"));
				ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
				ImGui::Checkbox(XORSTR("Bullet Tracers"), &Settings::ESP::BulletTracers::enabled);
				ImGui::Checkbox(XORSTR("Head Dot"), &Settings::ESP::HeadDot::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo(XORSTR("##BOXTYPE"), (int*)& Settings::ESP::Boxes::type, BoxTypes, IM_ARRAYSIZE(BoxTypes));
				ImGui::Combo(XORSTR("##CHAMSTYPE"), (int*)& Settings::ESP::Chams::type, ChamsTypes, IM_ARRAYSIZE(ChamsTypes));
				ImGui::Combo(XORSTR("##BARTYPE"), (int*)& Settings::ESP::Bars::type, BarTypes, IM_ARRAYSIZE(BarTypes));
				ImGui::Combo(XORSTR("##TRACERTYPE"), (int*)& Settings::ESP::Tracers::type, TracerTypes, IM_ARRAYSIZE(TracerTypes));
				ImGui::Combo(XORSTR("##BARCOLTYPE"), (int*)& Settings::ESP::Bars::colorType, BarColorTypes, IM_ARRAYSIZE(BarColorTypes));
				ImGui::Combo(XORSTR("##TEAMCOLTYPE"), (int*)& Settings::ESP::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox(XORSTR("Skeleton"), &Settings::ESP::Skeleton::enabled);
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat(XORSTR("##HDOTSIZE"), &Settings::ESP::HeadDot::size, 1.f, 10.f, XORSTR("Size: %0.3f"));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Filter"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Enemies"), &Settings::ESP::Filters::enemies);
				ImGui::Checkbox(XORSTR("Chickens"), &Settings::ESP::Filters::chickens);
				ImGui::Checkbox(XORSTR("LocalPlayer"), &Settings::ESP::Filters::localplayer);
				ImGui::Checkbox(XORSTR("Legit Mode"), &Settings::ESP::Filters::legit);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Allies"), &Settings::ESP::Filters::allies);
				ImGui::Checkbox(XORSTR("Fish"), &Settings::ESP::Filters::fishes);
				ImGui::Checkbox(XORSTR("Smoke Check"), &Settings::ESP::Filters::smokeCheck);
				ImGui::Checkbox(XORSTR("Visiblity Check"), &Settings::ESP::Filters::visibilityCheck);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Player Information"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Clan"), &Settings::ESP::Info::clan);
				ImGui::Checkbox(XORSTR("Rank"), &Settings::ESP::Info::rank);
				ImGui::PushID(1);
				ImGui::Checkbox(XORSTR("Health"), &Settings::ESP::Info::health);
				ImGui::PopID();
				ImGui::Checkbox(XORSTR("Scoped"), &Settings::ESP::Info::scoped);
				ImGui::Checkbox(XORSTR("Flashed"), &Settings::ESP::Info::flashed);
				ImGui::Checkbox(XORSTR("Defuse Kit"), &Settings::ESP::Info::hasDefuser);
				ImGui::Checkbox(XORSTR("Grabbing Hostage"), &Settings::ESP::Info::grabbingHostage);
				ImGui::Checkbox(XORSTR("Location"), &Settings::ESP::Info::location);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Name"), &Settings::ESP::Info::name);
				ImGui::Checkbox(XORSTR("Steam ID"), &Settings::ESP::Info::steamId);
				ImGui::Checkbox(XORSTR("Weapon"), &Settings::ESP::Info::weapon);
				ImGui::Checkbox(XORSTR("Reloading"), &Settings::ESP::Info::reloading);
				ImGui::Checkbox(XORSTR("Planting"), &Settings::ESP::Info::planting);
				ImGui::Checkbox(XORSTR("Defusing"), &Settings::ESP::Info::defusing);
				ImGui::Checkbox(XORSTR("Rescuing Hostage"), &Settings::ESP::Info::rescuing);
			}

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("World"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Weapons"), &Settings::ESP::Filters::weapons);
				ImGui::Checkbox(XORSTR("Throwables"), &Settings::ESP::Filters::throwables);
				ImGui::Checkbox(XORSTR("Entity Glow"), &Settings::ESP::Glow::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Bomb"), &Settings::ESP::Filters::bomb);
				ImGui::Checkbox(XORSTR("Defuse Kits"), &Settings::ESP::Filters::defusers);
				ImGui::Checkbox(XORSTR("Hostages"), &Settings::ESP::Filters::hostages);
			}
			ImGui::Columns(1);
			ImGui::EndChild();
			ImGui::EndChild();
		}
	}

	ImGui::NextColumn();
	{
		ImGui::BeginChild(XORSTR("Chams"), ImVec2(0, 0), true);
		{
			ImGui::Text(XORSTR("Crosshair"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Recoil Crosshair"), &Settings::Recoilcrosshair::enabled);
				ImGui::Checkbox(XORSTR("FOV Circle"), &Settings::ESP::FOVCrosshair::enabled);
				ImGui::Checkbox(XORSTR("Show Spread"), &Settings::ESP::Spread::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Only When Shooting"), &Settings::Recoilcrosshair::showOnlyWhenShooting);
				ImGui::Checkbox(XORSTR("Filled"), &Settings::ESP::FOVCrosshair::filled);
				ImGui::Checkbox(XORSTR("Show SpreadLimit"), &Settings::ESP::Spread::spreadLimit);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Skybox Changer"));
			ImGui::Separator();
			ImGui::Checkbox(XORSTR("##SKYBOXENABLE"), &Settings::SkyBox::enabled);
			ImGui::SameLine();
			ImGui::Combo(XORSTR("##SKYBOX"), &Settings::SkyBox::skyBoxNumber, SkyBoxes, IM_ARRAYSIZE(SkyBoxes));
			ImGui::Separator();
			ImGui::Text(XORSTR("Other Visual Settings"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Arms"), &Settings::ESP::Chams::Arms::enabled);
				ImGui::Checkbox(XORSTR("Dlights"), &Settings::Dlights::enabled);
				ImGui::Checkbox(XORSTR("No Flash"), &Settings::Noflash::enabled);
				ImGui::Checkbox(XORSTR("Show Footsteps"), &Settings::ESP::Sounds::enabled);
				ImGui::Checkbox(XORSTR("No View Punch"), &Settings::View::NoViewPunch::enabled);
				ImGui::Checkbox(XORSTR("Weapons"), &Settings::ESP::Chams::Weapon::enabled);
				ImGui::Checkbox(XORSTR("No Sky"), &Settings::NoSky::enabled);
				ImGui::Checkbox(XORSTR("No Smoke"), &Settings::NoSmoke::enabled);


				if(ImGui::Button(XORSTR("Tracer Effect"), ImVec2(-1, 0)))
					ImGui::OpenPopup(XORSTR("##TracerEffectWindow"));
				ImGui::SetNextWindowSize(ImVec2(320,120), ImGuiSetCond_Always);
				if( ImGui::BeginPopup(XORSTR("##TracerEffectWindow")) )
				{
					ImGui::PushItemWidth(-1);
                    if( Settings::TracerEffects::serverSide )
                    {
                        Settings::TracerEffects::frequency = 1;
                        Settings::TracerEffects::effect = TracerEffects_t::TASER;
                    }
					ImGui::Combo(XORSTR("##TracerEffects"), (int*)& Settings::TracerEffects::effect, tracerEffectNames, IM_ARRAYSIZE(tracerEffectNames));
					ImGui::Checkbox(XORSTR("Enable Tracers"), &Settings::TracerEffects::enabled);
                    ImGui::Checkbox(XORSTR("Server Sided?"), &Settings::TracerEffects::serverSide);
                    SetTooltip(XORSTR("Requires a Taser in your Inventory.\nCan only shoot one shot at a time\nOnly Works with Kisak Snot"));
                    ImGui::Columns(2, NULL, false);
                    {
                        ImGui::SliderInt(XORSTR("##TracerFreq"),&Settings::TracerEffects::frequency, 0, 10, XORSTR("Freq: %0.f"));
                    }
                    ImGui::NextColumn();
                    {
                        if( ImGui::Button(XORSTR("Restore Tracers")) ){
                            TracerEffect::RestoreTracers();
                        }
                    }
					ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::Combo(XORSTR("##ARMSTYPE"), (int*)& Settings::ESP::Chams::Arms::type, ArmsTypes, IM_ARRAYSIZE(ArmsTypes));
				ImGui::SliderFloat(XORSTR("##DLIGHTRADIUS"), &Settings::Dlights::radius, 0, 1000, XORSTR("Radius: %0.f"));
				ImGui::SliderFloat(XORSTR("##NOFLASHAMOUNT"), &Settings::Noflash::value, 0, 255, XORSTR("Amount: %0.f"));
				ImGui::SliderInt(XORSTR("##SOUNDSTIME"), &Settings::ESP::Sounds::time, 250, 5000, XORSTR("Timeout: %0.f"));
				ImGui::PopItemWidth();
				ImGui::Checkbox(XORSTR("No Aim Punch"), &Settings::View::NoAimPunch::enabled);
				ImGui::Checkbox(XORSTR("ASUS Walls"), &Settings::ASUSWalls::enabled);
				ImGui::Checkbox(XORSTR("No Scope Border"), &Settings::NoScopeBorder::enabled);
				ImGui::Checkbox(XORSTR("Autowall Debug"), &Settings::ESP::AutoWall::debugView);
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Radar"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Radar"), &Settings::Radar::enabled);
				ImGui::PushItemWidth(-1);
				ImGui::Combo(XORSTR("##RADARTEAMCOLTYPE"), (int*)& Settings::Radar::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
				ImGui::PopItemWidth();
				ImGui::Checkbox(XORSTR("Enemies"), &Settings::Radar::enemies);
				ImGui::Checkbox(XORSTR("Bomb"), &Settings::Radar::bomb);
				ImGui::Checkbox(XORSTR("Legit"), &Settings::Radar::legit);
				ImGui::Checkbox(XORSTR("In-game Radar"), &Settings::Radar::InGame::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat(XORSTR("##RADARZOOM"), &Settings::Radar::zoom, 0.f, 100.f, XORSTR("Zoom: %0.f"));
				ImGui::SliderFloat(XORSTR("##RADARICONSSCALE"), &Settings::Radar::iconsScale, 2, 16, XORSTR("Icons Scale: %0.1f"));
				ImGui::PopItemWidth();
				ImGui::Checkbox(XORSTR("Allies"), &Settings::Radar::allies);
				ImGui::Checkbox(XORSTR("Defuser"), &Settings::Radar::defuser);
				ImGui::Checkbox(XORSTR("Visibility Check"), &Settings::Radar::visibilityCheck);
				ImGui::Checkbox(XORSTR("Smoke Check"), &Settings::Radar::smokeCheck);
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::Text(XORSTR("Hitmarkers"));
			ImGui::Separator();
			ImGui::Columns(2, NULL, true);
			{
				ImGui::Checkbox(XORSTR("Hitmarkers"), &Settings::ESP::Hitmarker::enabled);

				ImGui::Checkbox(XORSTR("Enemies##HITMARKERS"), &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox(XORSTR("Allies##HITMARKERS"), &Settings::ESP::Hitmarker::allies);
				ImGui::Checkbox(XORSTR("Damage##HITMARKERS"), &Settings::ESP::Hitmarker::Damage::enabled);
			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt(XORSTR("##HITMARKERDUR"), &Settings::ESP::Hitmarker::duration, 250, 3000, XORSTR("Timeout: %0.f"));
				ImGui::SliderInt(XORSTR("##HITMARKERSIZE"), &Settings::ESP::Hitmarker::size, 1, 32, XORSTR("Size: %0.f"));
				ImGui::SliderInt(XORSTR("##HITMARKERGAP"), &Settings::ESP::Hitmarker::innerGap, 1, 16, XORSTR("Gap: %0.f"));
				ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}
