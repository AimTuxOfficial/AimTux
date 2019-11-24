#include "visualstab.h"

#include "../../settings.h"
#include "../../Utils/xorstring.h"
#include "../../ImGUI/imgui_internal.h"
#include "../atgui.h"
#include "../../Hacks/tracereffect.h"
#include "../../Hacks/materialconfig.h"

#pragma GCC diagnostic ignored "-Wformat-security"

void Visuals::RenderTab()
{
	const char* BackendTypes[] = { "Surface (Valve)", "ImGUI (Custom/Faster)" };
	const char* BoxTypes[] = { "Flat 2D", "Frame 2D", "Box 3D", "Hitboxes" };
	const char* SpriteTypes[] = { "Tux" };
	const char* TracerTypes[] = { "Bottom", "Cursor" };
	const char* BarTypes[] = { "Vertical Left", "Vertical Right", "Horizontal Below", "Horizontal Above", "Interwebz" };
	const char* BarColorTypes[] = { "Static", "Health Based" };
	const char* TeamColorTypes[] = { "Absolute", "Relative" };
	const char* ChamsTypes[] = { "Normal", "Normal - XQZ", "Flat", "Flat - XQZ" };
	const char* ArmsTypes[] = { "Default", "Wireframe", "None" };
	const char* WeaponTypes[] = { "Default", "Wireframe", "None" };
	const char* SmokeTypes[] = { "Wireframe", "None" };
    const char* Sounds[] = { "None", "SpongeBob", "Half life", "Half life 2", "Half life 3", "Half life 4", "BB Gun Bell", "Dopamine", "Wub", "Pedo Yes!", "Meme", "Error", "Orchestral" };
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

	ImGui::Columns(2, nullptr, true);
	{
		ImGui::Checkbox(XORSTR("Enabled"), &Settings::ESP::enabled);
        ImGui::Combo( XORSTR( "##BACKENDTYPE" ), (int*)&Settings::ESP::backend, BackendTypes, IM_ARRAYSIZE( BackendTypes ) );

        ImGui::NextColumn();
		ImGui::Text(XORSTR("Only on Key"));
		UI::KeyBindButton(&Settings::ESP::key);
	}
	ImGui::Separator();

	ImGui::Columns(2, nullptr, true);
	{
		ImGui::BeginChild(XORSTR("COL1"), ImVec2(0, 0), true);
		{
			ImGui::Text(XORSTR("ESP"));
			ImGui::BeginChild(XORSTR("ESP"), ImVec2(0, 0), true);
			ImGui::Text(XORSTR("Type"));
			ImGui::Separator();
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Outline Box"), &Settings::ESP::Boxes::enabled);
				ImGui::Checkbox(XORSTR("Sprite ESP"), &Settings::ESP::Sprite::enabled);
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
				ImGui::Combo(XORSTR("##SPRITETYPE"), (int*)& Settings::ESP::Sprite::type, SpriteTypes, IM_ARRAYSIZE(SpriteTypes));
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
			ImGui::Columns(2, nullptr, true);
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
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Clan"), &Settings::ESP::Info::clan);
				ImGui::Checkbox(XORSTR("Rank"), &Settings::ESP::Info::rank);
				ImGui::PushID(1);
				ImGui::Checkbox(XORSTR("Health"), &Settings::ESP::Info::health);
				ImGui::PopID();
				ImGui::Checkbox(XORSTR("Armor"), &Settings::ESP::Info::armor);
				ImGui::Checkbox(XORSTR("Scoped"), &Settings::ESP::Info::scoped);
				ImGui::Checkbox(XORSTR("Flashed"), &Settings::ESP::Info::flashed);
				ImGui::Checkbox(XORSTR("Defuse Kit"), &Settings::ESP::Info::hasDefuser);
				ImGui::Checkbox(XORSTR("Grabbing Hostage"), &Settings::ESP::Info::grabbingHostage);
				ImGui::Checkbox(XORSTR("Location"), &Settings::ESP::Info::location);
				ImGui::Checkbox(XORSTR("Money"), &Settings::ESP::Info::money);
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
                ImGui::Checkbox(XORSTR("Layers Debug"), &Settings::Debug::AnimLayers::draw);
            }

			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("World"));
			ImGui::Separator();
			ImGui::Columns(2, nullptr, true);
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

			ImGui::Separator();
			ImGui::Text(XORSTR("Danger Zone"));
			ImGui::Separator();
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Loot Crates"), &Settings::ESP::DangerZone::lootcrate);
				ImGui::Checkbox(XORSTR("Weapon Upgrades"), &Settings::ESP::DangerZone::upgrade);
				ImGui::Checkbox(XORSTR("Ammo box"), &Settings::ESP::DangerZone::ammobox);
				ImGui::Checkbox(XORSTR("Radar Jammer"), &Settings::ESP::DangerZone::radarjammer);
				ImGui::Checkbox(XORSTR("Cash"), &Settings::ESP::DangerZone::cash);
				ImGui::Checkbox(XORSTR("Drone"), &Settings::ESP::DangerZone::drone);
				ImGui::Checkbox(XORSTR("Draw Distance"), &Settings::ESP::DangerZone::drawDistEnabled);
			}
			ImGui::NextColumn();
			{
				ImGui::Checkbox(XORSTR("Safe"), &Settings::ESP::DangerZone::safe);
				ImGui::Checkbox(XORSTR("Sentry Turret"), &Settings::ESP::DangerZone::dronegun);
				ImGui::Checkbox(XORSTR("Melee"), &Settings::ESP::DangerZone::melee);
				ImGui::Checkbox(XORSTR("Tablet"), &Settings::ESP::DangerZone::tablet);
				ImGui::Checkbox(XORSTR("Healthshot"), &Settings::ESP::DangerZone::healthshot);
				ImGui::Checkbox(XORSTR("Explosive Barrel"), &Settings::ESP::DangerZone::barrel);
				if (Settings::ESP::DangerZone::drawDistEnabled)
					ImGui::SliderInt(XORSTR("##DZDRAWDIST"), &Settings::ESP::DangerZone::drawDist, 1, 10000, XORSTR("Amount: %0.f"));
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Event logger"));
			ImGui::Separator();
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Show Enemies"), &Settings::Eventlog::showEnemies);
				ImGui::Checkbox(XORSTR("Show Allies"), &Settings::Eventlog::showTeammates);

			}
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderFloat(XORSTR("##LOGGERDURATION"), &Settings::Eventlog::duration, 1000.f, 5000.f, XORSTR("Log duration: %0.f"));
				ImGui::SliderFloat(XORSTR("##LOGGERLINES"), &Settings::Eventlog::lines, 5, 15, XORSTR("Log lines: %0.f"));
				ImGui::Checkbox(XORSTR("Show LocalPlayer"), &Settings::Eventlog::showLocalplayer);
				ImGui::PopItemWidth();
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
			ImGui::Columns(2, nullptr, true);
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
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Arms"), &Settings::ESP::Chams::Arms::enabled);
				ImGui::Checkbox(XORSTR("Weapons"), &Settings::ESP::Chams::Weapon::enabled);
				ImGui::Checkbox(XORSTR("Dlights"), &Settings::Dlights::enabled);
				ImGui::Checkbox(XORSTR("No Flash"), &Settings::Noflash::enabled);
				ImGui::Checkbox(XORSTR("No Smoke"), &Settings::NoSmoke::enabled);
				ImGui::Checkbox(XORSTR("Show Footsteps"), &Settings::ESP::Sounds::enabled);
				ImGui::Checkbox(XORSTR("No View Punch"), &Settings::View::NoViewPunch::enabled);
				ImGui::Checkbox(XORSTR("No Sky"), &Settings::NoSky::enabled);

				if ( ImGui::Button( XORSTR( "Material Config" ), ImVec2( -1, 0 ) ) )
					ImGui::OpenPopup( XORSTR( "##MaterialConfigWindow" ) );
				SetTooltip( XORSTR( "Advanced CSGO Gfx Settings\nExperimental" ) );
				ImGui::SetNextWindowSize( ImVec2( 320, 640 ), ImGuiSetCond_Always );
				if ( ImGui::BeginPopup( XORSTR( "##MaterialConfigWindow" ) ) ) {
					ImGui::PushItemWidth( -1 );
					if ( ImGui::Button( XORSTR( "Reset Changes" ) ) ) {
						Settings::MaterialConfig::config = MaterialConfig::backupConfig;
					}
					ImGui::Checkbox( XORSTR( "Changes Enabled?" ), &Settings::MaterialConfig::enabled );
					SetTooltip( XORSTR( "Expect some lag when changing these settings.\nIf your hud breaks, toggle cl_drawhud off/on" ) );
					ImGui::SliderFloat( XORSTR( "##MONITORGAMMA" ), &Settings::MaterialConfig::config.m_fMonitorGamma, 0.1f, 12.0f,
                                        XORSTR( "Gamma: %.3f" ) );
					ImGui::SliderFloat( XORSTR( "##GAMMATVRANGEMIN" ), &Settings::MaterialConfig::config.m_fGammaTVRangeMin,
										0.1f, std::min( 300.0f, Settings::MaterialConfig::config.m_fGammaTVRangeMax ),
										XORSTR( "TVRangeMin: %.3f" ) );
					ImGui::SliderFloat( XORSTR( "##GAMMATVRANGEMAX" ), &Settings::MaterialConfig::config.m_fGammaTVRangeMax,
										Settings::MaterialConfig::config.m_fGammaTVRangeMin, 300.0f,
										XORSTR( "TVRangeMax: %.3f" ) );
					ImGui::SliderFloat( XORSTR( "##GAMMATVEXPONENT" ), &Settings::MaterialConfig::config.m_fGammaTVExponent,
										0.1f, 3.0f, XORSTR( "TV Exponent: %.3f" ) );
					ImGui::Checkbox( XORSTR( "GammaTVEnabled" ), &Settings::MaterialConfig::config.m_bGammaTVEnabled );
					ImGui::Text( XORSTR( "Width:" ) );
					ImGui::SameLine();
					ImGui::InputInt( XORSTR( "##GAMEWIDTH" ), &Settings::MaterialConfig::config.m_VideoMode.m_Width );

					ImGui::Text( XORSTR( "Height:" ) );
					ImGui::SameLine();
					ImGui::InputInt( XORSTR( "##GAMEHEIGHT" ), &Settings::MaterialConfig::config.m_VideoMode.m_Height );

					ImGui::Text( XORSTR( "Refresh Rate:" ) );
					ImGui::SameLine();
					ImGui::InputInt( XORSTR( "##GAMEREFRESHRATE" ),
									 &Settings::MaterialConfig::config.m_VideoMode.m_RefreshRate );

					ImGui::Checkbox( XORSTR( "TripleBuffered" ), &Settings::MaterialConfig::config.m_bTripleBuffered );
					ImGui::SliderInt( XORSTR( "##AASAMPLES" ), &Settings::MaterialConfig::config.m_nAASamples, 0, 16, XORSTR( "AA Samples: %1.f" ) );
					ImGui::SliderInt( XORSTR( "##FORCEANISOTROPICLEVEL" ), &Settings::MaterialConfig::config.m_nForceAnisotropicLevel, 0, 8, XORSTR( "Anisotropic Level: %1.f" ) );
					ImGui::SliderInt( XORSTR( "##SKIPMIPLEVELS" ), &Settings::MaterialConfig::config.skipMipLevels, 0, 10, XORSTR( "SkipMipLevels: %1.f" ) );
					SetTooltip( XORSTR( "Makes the game flatter.") );
					if ( ImGui::Button( XORSTR( "Flags" ), ImVec2( -1, 0 ) ) )
						ImGui::OpenPopup( XORSTR( "##MaterialConfigFlags" ) );
					ImGui::SetNextWindowSize( ImVec2( 320, 240 ), ImGuiSetCond_Always );
					if ( ImGui::BeginPopup( XORSTR( "##MaterialConfigFlags" ) ) ) {
						ImGui::PushItemWidth( -1 );

						static bool localFlags[] = {
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_WINDOWED ) != 0, // ( 1 << 0 )
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_RESIZING ) != 0, // ( 1 << 1 )
								false, // ( 1 << 2 ) is not used.
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_NO_WAIT_FOR_VSYNC ) != 0, // ( 1 << 3 )
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_STENCIL ) != 0, // ...
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_FORCE_TRILINEAR ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_FORCE_HWSYNC ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_DISABLE_SPECULAR ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_DISABLE_BUMPMAP ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_ENABLE_PARALLAX_MAPPING ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_USE_Z_PREFILL ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_REDUCE_FILLRATE ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_ENABLE_HDR ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_LIMIT_WINDOWED_SIZE ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_SCALE_TO_OUTPUT_RESOLUTION ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_USING_MULTIPLE_WINDOWS ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_DISABLE_PHONG ) != 0,
								( Settings::MaterialConfig::config.m_Flags & MaterialSystem_Config_Flags_t::MATSYS_VIDCFG_FLAGS_VR_MODE ) != 0
						};

						ImGui::Checkbox( XORSTR( "Windowed" ), &localFlags[0] );
						ImGui::Checkbox( XORSTR( "Resizing" ), &localFlags[1] );
						ImGui::Checkbox( XORSTR( "No VSYNC Wait" ), &localFlags[3] );
						ImGui::Checkbox( XORSTR( "Stencil" ), &localFlags[4] );
						ImGui::Checkbox( XORSTR( "Force Tri-Linear" ), &localFlags[5] );
						ImGui::Checkbox( XORSTR( "Force HW Sync" ), &localFlags[6] );
						ImGui::Checkbox( XORSTR( "Disable Specular" ), &localFlags[7] );
						ImGui::Checkbox( XORSTR( "Disable Bumpmap" ), &localFlags[8] );
						ImGui::Checkbox( XORSTR( "Disable Phong" ), &localFlags[16] );
						ImGui::Checkbox( XORSTR( "Parallax Mapping" ), &localFlags[9] );
						ImGui::Checkbox( XORSTR( "Use Z-Prefill" ), &localFlags[10] );
						ImGui::Checkbox( XORSTR( "Reduce FillRate" ), &localFlags[11] );
						ImGui::Checkbox( XORSTR( "HDR" ), &localFlags[12] );
						ImGui::Checkbox( XORSTR( "Limit Windowed Size" ), &localFlags[13] );
						ImGui::Checkbox( XORSTR( "Scale to Output Resolution" ), &localFlags[14] );
						ImGui::Checkbox( XORSTR( "Using Multiple Windows" ), &localFlags[15] );
						ImGui::Checkbox( XORSTR( "VR-Mode" ), &localFlags[17] );

						if ( ImGui::Button( XORSTR( "Apply " ) ) ) {
							for ( unsigned short i = 0; i < 18; i++ ) {
								if ( i == 2 ) // ( 1 << 2 ) not used.
									continue;
								Settings::MaterialConfig::config.SetFlag( ( unsigned int ) ( 1 << i ), localFlags[i] );
							}
						}

						ImGui::PopItemWidth();
						ImGui::EndPopup();
					}
					//m_flags
					ImGui::Checkbox( XORSTR( "EditMode" ), &Settings::MaterialConfig::config.bEditMode );
					//proxiesTestMode
					ImGui::Checkbox( XORSTR ( "Compressed Textures" ),
									 &Settings::MaterialConfig::config.bCompressedTextures );
					ImGui::Checkbox( XORSTR( "Filter Lightmaps" ), &Settings::MaterialConfig::config.bFilterLightmaps );
					ImGui::Checkbox( XORSTR( "Filter Textures" ), &Settings::MaterialConfig::config.bFilterTextures );
					ImGui::Checkbox( XORSTR( "Reverse Depth" ), &Settings::MaterialConfig::config.bReverseDepth );
					ImGui::Checkbox( XORSTR( "Buffer Primitives" ), &Settings::MaterialConfig::config.bBufferPrimitives );
					ImGui::Checkbox( XORSTR( "Draw Flat" ), &Settings::MaterialConfig::config.bDrawFlat );
					ImGui::Checkbox( XORSTR( "Measure Fill-Rate" ), &Settings::MaterialConfig::config.bMeasureFillRate );
					ImGui::Checkbox( XORSTR( "Visualize Fill-Rate" ),
									 &Settings::MaterialConfig::config.bVisualizeFillRate );
					ImGui::Checkbox( XORSTR( "No Transparency" ), &Settings::MaterialConfig::config.bNoTransparency );
					ImGui::Checkbox( XORSTR( "Software Lighting" ),
									 &Settings::MaterialConfig::config.bSoftwareLighting ); // Crashes game
					//AllowCheats ?
					ImGui::SliderInt( XORSTR( "##MIPLEVELS" ), ( int* ) &Settings::MaterialConfig::config.nShowMipLevels, 0,
									  3, XORSTR( "ShowMipLevels: %1.f" ) );
					ImGui::Checkbox( XORSTR( "Show Low-Res Image" ), &Settings::MaterialConfig::config.bShowLowResImage );
					ImGui::Checkbox( XORSTR( "Show Normal Map" ), &Settings::MaterialConfig::config.bShowNormalMap );
					ImGui::Checkbox( XORSTR( "MipMap Textures" ), &Settings::MaterialConfig::config.bMipMapTextures );
					ImGui::SliderInt( XORSTR( "##NFULLBRIGHT" ), ( int* ) &Settings::MaterialConfig::config.nFullbright, 0, 3, XORSTR( "nFullBright: %1.f" ) );
					SetTooltip( XORSTR( "1 = Bright World, 2 = Bright Models" ) );
					ImGui::Checkbox( XORSTR( "Fast NoBump" ), &Settings::MaterialConfig::config.m_bFastNoBump );
					ImGui::Checkbox( XORSTR( "Suppress Rendering" ),
									 &Settings::MaterialConfig::config.m_bSuppressRendering );
					ImGui::Checkbox( XORSTR( "Draw Gray" ), &Settings::MaterialConfig::config.m_bDrawGray );
					ImGui::Checkbox( XORSTR( "Show Specular" ), &Settings::MaterialConfig::config.bShowSpecular );
					ImGui::Checkbox( XORSTR( "Show Defuse" ), &Settings::MaterialConfig::config.bShowDiffuse );
					ImGui::SliderInt( XORSTR( "##AAQUALITY" ), &Settings::MaterialConfig::config.m_nAAQuality, 0, 16,
									  XORSTR( "AAQuality: %1.f" ) );
					ImGui::Checkbox( XORSTR( "Shadow Depth Texture" ),
									 &Settings::MaterialConfig::config.m_bShadowDepthTexture );
					SetTooltip( XORSTR( "Risky. May cause black Screen. Reset if it does." ) );
					ImGui::Checkbox( XORSTR( "Motion Blur" ), &Settings::MaterialConfig::config.m_bMotionBlur );
					ImGui::Checkbox( XORSTR( "Support Flashlight" ),
									 &Settings::MaterialConfig::config.m_bSupportFlashlight );
					ImGui::Checkbox( XORSTR( "Paint Enabled" ), &Settings::MaterialConfig::config.m_bPaintEnabled );
					// VRMode Adapter?
					ImGui::PopItemWidth();
					ImGui::EndPopup();
				}
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
                    ImGui::Columns(2, nullptr, false);
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
				ImGui::Combo(XORSTR("##WEAPONTYPE"), (int*)& Settings::ESP::Chams::Weapon::type, WeaponTypes, IM_ARRAYSIZE(WeaponTypes));
				ImGui::SliderFloat(XORSTR("##DLIGHTRADIUS"), &Settings::Dlights::radius, 0, 1000, XORSTR("Radius: %0.f"));
				ImGui::SliderFloat(XORSTR("##NOFLASHAMOUNT"), &Settings::Noflash::value, 0, 255, XORSTR("Amount: %0.f"));
				ImGui::Combo(XORSTR("##SMOKETYPE"), (int*)& Settings::NoSmoke::type, SmokeTypes, IM_ARRAYSIZE(SmokeTypes));
				ImGui::SliderInt(XORSTR("##SOUNDSTIME"), &Settings::ESP::Sounds::time, 250, 5000, XORSTR("Timeout: %0.f"));
				ImGui::PopItemWidth();
				ImGui::Checkbox( XORSTR( "Grenade Prediction" ), &Settings::GrenadePrediction::enabled );
				ImGui::Checkbox(XORSTR("No Aim Punch"), &Settings::View::NoAimPunch::enabled);
				ImGui::Checkbox(XORSTR("ASUS Walls"), &Settings::ASUSWalls::enabled);
				ImGui::Checkbox(XORSTR("No Scope Border"), &Settings::NoScopeBorder::enabled);
				ImGui::Checkbox(XORSTR("Autowall Debug"), &Settings::Debug::AutoWall::debugView);
				ImGui::Checkbox(XORSTR("AimSpot Debug"), &Settings::Debug::AutoAim::drawTarget);
				ImGui::Checkbox(XORSTR("BoneMap Debug"), &Settings::Debug::BoneMap::draw);
				if( Settings::Debug::BoneMap::draw )
					ImGui::Checkbox(XORSTR("Just Dots"), &Settings::Debug::BoneMap::justDrawDots);
				ImGui::SliderInt(XORSTR("Test Model ID"), &Settings::Debug::BoneMap::modelID, 1253, 1350, XORSTR("Model ID: %0.f") );
			}
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::Text(XORSTR("Radar"));
			ImGui::Separator();
			ImGui::Columns(2, nullptr, true);
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
			ImGui::Columns(2, nullptr, true);
			{
				ImGui::Checkbox(XORSTR("Hitmarkers"), &Settings::ESP::Hitmarker::enabled);

				ImGui::Checkbox(XORSTR("Enemies##HITMARKERS"), &Settings::ESP::Hitmarker::enemies);
				ImGui::Checkbox(XORSTR("Allies##HITMARKERS"), &Settings::ESP::Hitmarker::allies);
                ImGui::Checkbox(XORSTR("Sounds##HITMARKERS"), &Settings::ESP::Hitmarker::Sounds::enabled);
                ImGui::Checkbox(XORSTR("Damage##HITMARKERS"), &Settings::ESP::Hitmarker::Damage::enabled);
            }
			ImGui::NextColumn();
			{
				ImGui::PushItemWidth(-1);
				ImGui::SliderInt(XORSTR("##HITMARKERDUR"), &Settings::ESP::Hitmarker::duration, 250, 3000, XORSTR("Timeout: %0.f"));
				ImGui::SliderInt(XORSTR("##HITMARKERSIZE"), &Settings::ESP::Hitmarker::size, 1, 32, XORSTR("Size: %0.f"));
				ImGui::SliderInt(XORSTR("##HITMARKERGAP"), &Settings::ESP::Hitmarker::innerGap, 1, 16, XORSTR("Gap: %0.f"));
                ImGui::Combo( XORSTR ( "Sounds##HITMARKERCOMBO" ), ( int* ) &Settings::ESP::Hitmarker::Sounds::sound, Sounds, IM_ARRAYSIZE( Sounds ) );
                ImGui::PopItemWidth();
			}
			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::EndChild();
		}
	}
	ImGui::Columns(1);
}
