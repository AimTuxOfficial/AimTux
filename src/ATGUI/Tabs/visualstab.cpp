#include "visualstab.h"

void Visuals::RenderTab()
{
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Wireframe", "None" };

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
				ImGui::Checkbox("Filled", &Settings::ESP::FOVCrosshair::filled);
				SetTooltip("Fill the fov circle");
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
				ImGui::Combo("##RADARTEAMCOLTYPE", (int*)& Settings::Radar::teamColorType, TeamColorTypes, IM_ARRAYSIZE(TeamColorTypes));
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
