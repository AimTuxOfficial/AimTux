#include "hvhtab.h"

void HvH::RenderTab()
{
	const char* yTypes[] = {
			"SLOW SPIN", "FAST SPIN", "JITTER", "BACKJITTER", "SIDE", "BACKWARDS", "FORWARDS", "LEFT", "RIGHT", "STATIC", "STATIC JITTER", "STATIC SMALL JITTER", // safe
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
			ImGui::EndChild();
		}
	}
}
