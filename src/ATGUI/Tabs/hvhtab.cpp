#include "hvhtab.h"

void HvH::RenderTab()
{
	const char* yTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "BACKJITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", "LUA", "LUA2", "CASUALAA",// safe
			"LISP", "LISP SIDE", "LISP JITTER", "ANGEL BACKWARDS", "ANGEL INVERSE", "ANGEL SPIN", "LOWERBODY", "LBYONGROUND", "LUA UNCLAMPED", "LUA UNCLAMPED2", // untrusted
	};

	const char* xTypes[] = {
			"UP", "DOWN", "DANCE", "FRONT", "LUA", // safe
			"FAKE UP", "FAKE DOWN", "LISP DOWN", "ANGEL DOWN", "ANGEL UP", "LUA UNCLAMPED" // untrusted
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
						ImGui::SliderFloat("##EDGEDISTANCE", &Settings::AntiAim::HeadEdge::distance, 20, 30, "Distance: %0.f");
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

			ImGui::Separator();
			ImGui::Checkbox("Lua Debug Mode", &Settings::AntiAim::Lua::debugMode);
			SetTooltip("Turns ON/OFF Lua Syntax/Runtime error checking.\n *Errors found in CSGO Console\nCan be turned off once Script is done for more speed.");
			if( Settings::AntiAim::Pitch::type == AntiAimType_X::LUA1 || Settings::AntiAim::Pitch::type == AntiAimType_X ::LUA_UNCLAMPED )
			{
				ImGui::Text("Lua AntiAim Editor -- X Axis");
				ImGui::InputTextMultiline("##LUAX", Settings::AntiAim::Lua::scriptX, sizeof(Settings::AntiAim::Lua::scriptX));
			}
			ImGui::Separator();

			if( ((Settings::AntiAim::Yaw::type == Settings::AntiAim::Yaw::typeFake) && // if they are equal to each other and a LUA type
						(Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA1 ||
						Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA2  ||
						Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED ||
						Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED2))
				|| // OR
					( (Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA1 && Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA_UNCLAMPED)// Any LUA types that use the same underlying script.
					 || (Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA2 && Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA_UNCLAMPED2)
					 || (Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED && Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA1)
					 || (Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED2 && Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA2)
					)
				)
		    {
				ImGui::Text("Lua AntiAim Editor -- Y Axis(BOTH)");
				if( Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA1 || Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED )
				{
					ImGui::InputTextMultiline("##LUAY", Settings::AntiAim::Lua::scriptY, sizeof(Settings::AntiAim::Lua::scriptY));
				}
				else
				{
					ImGui::InputTextMultiline("##LUAY2", Settings::AntiAim::Lua::scriptY2, sizeof(Settings::AntiAim::Lua::scriptY2));
				}
			}
			else
			{
				if ( Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA1 || Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED )
				{
					ImGui::Text("Lua AntiAim Editor -- Y Axis(ACTUAL)");
					ImGui::InputTextMultiline("##LUAY", Settings::AntiAim::Lua::scriptY, sizeof(Settings::AntiAim::Lua::scriptY));
				}
				else if ( Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA2 || Settings::AntiAim::Yaw::type == AntiAimType_Y::LUA_UNCLAMPED2 )
				{
					ImGui::Text("Lua AntiAim Editor -- Y2 Axis(ACTUAL)");
					ImGui::InputTextMultiline("##LUAY2", Settings::AntiAim::Lua::scriptY2, sizeof(Settings::AntiAim::Lua::scriptY2));
				}
				ImGui::Separator();
				if( Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA1 || Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA_UNCLAMPED )
				{
					ImGui::Text("Lua AntiAim Editor -- Y Axis(FAKE)");
					ImGui::InputTextMultiline("##LUAY", Settings::AntiAim::Lua::scriptY, sizeof(Settings::AntiAim::Lua::scriptY));
				}
				else if( Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA2 || Settings::AntiAim::Yaw::typeFake == AntiAimType_Y::LUA_UNCLAMPED2 )
				{
					ImGui::Text("Lua AntiAim Editor -- Y2 Axis (FAKE)");
					ImGui::InputTextMultiline("##LUAY2", Settings::AntiAim::Lua::scriptY2, sizeof(Settings::AntiAim::Lua::scriptY2));
				}
			}
			ImGui::EndChild();
		}
	}
}
