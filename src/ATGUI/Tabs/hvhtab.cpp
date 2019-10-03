#include "hvhtab.h"

#include "../../interfaces.h"
#include "../../Utils/xorstring.h"
#include "../../settings.h"
#include "../../Hacks/valvedscheck.h"
#include "../../ImGUI/imgui_internal.h"

#pragma GCC diagnostic ignored "-Wformat-security"

void HvH::RenderTab()
{
    const char* yTypes[] = {
            "NONE", "MAX_DELTA_LEFT", "MAX_DELTA_RIGHT", "MAX_DELTA_FLIPPER", "MAX_DELTA_LBY_AVOID"
    };

    const char* xTypes[] = {
            "UP", "DOWN", "DANCE", "FRONT", // safe
            "FAKE UP", "FAKE DOWN", "LISP DOWN", "ANGEL DOWN", "ANGEL UP" // untrusted
    };

    ImGui::Columns(2, nullptr, true);
    {
        ImGui::BeginChild(XORSTR("HVH1"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("AntiAim"));
            ImGui::BeginChild(XORSTR("##ANTIAIM"), ImVec2(0, 0), true);
            {
                ImGui::Checkbox(XORSTR("Yaw"), &Settings::AntiAim::Yaw::enabled);
                ImGui::Separator();
                ImGui::Columns(2, nullptr, true);
                {
                    ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
                    ImGui::Text(XORSTR("Yaw Fake"));
                    ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
                    ImGui::Text(XORSTR("Yaw Actual"));
                }
                ImGui::NextColumn();
                {
                    ImGui::PushItemWidth(-1);
                    ImGui::Combo(XORSTR("##YFAKETYPE"), (int*)& Settings::AntiAim::Yaw::typeFake, yTypes, IM_ARRAYSIZE(yTypes));

                    ImGui::Combo(XORSTR("##YACTUALTYPE"), (int*)& Settings::AntiAim::Yaw::type, yTypes, IM_ARRAYSIZE(yTypes));
                    ImGui::PopItemWidth();
                }
                ImGui::Columns(1);
                ImGui::Separator();
                ImGui::Checkbox(XORSTR("Pitch"), &Settings::AntiAim::Pitch::enabled);
                ImGui::Separator();
                ImGui::Columns(2, nullptr, true);
                {
                    ImGui::ItemSize(ImVec2(0.0f, 0.0f), 0.0f);
                    ImGui::Text(XORSTR("Pitch Actual"));
                }
                ImGui::NextColumn();
                {
                    ImGui::PushItemWidth(-1);
                    if (ImGui::Combo(XORSTR("##XTYPE"), (int*)& Settings::AntiAim::Pitch::type, xTypes, IM_ARRAYSIZE(xTypes)))
                    {
                        if (!ValveDSCheck::forceUT && ((*csGameRules) && (*csGameRules)->IsValveDS()) && Settings::AntiAim::Pitch::type >= AntiAimType_X::STATIC_UP_FAKE)
                        {
                            Settings::AntiAim::Pitch::type = AntiAimType_X::STATIC_UP;
                            ImGui::OpenPopup(XORSTR("Error###UNTRUSTED_AA"));
                        }
                    }
                    ImGui::PopItemWidth();
                }
                ImGui::Columns(1);
                ImGui::Separator();
                ImGui::Text(XORSTR("Disable"));
                ImGui::Separator();
                ImGui::Checkbox(XORSTR("Knife"), &Settings::AntiAim::AutoDisable::knifeHeld);
                ImGui::Checkbox(XORSTR("No Enemy"), &Settings::AntiAim::AutoDisable::noEnemy);

                ImGui::Columns(1);
                ImGui::Separator();
                ImGui::Text(XORSTR("Edging"));
                ImGui::Separator();
                ImGui::Columns(2, nullptr, true);
                {
                    ImGui::Checkbox(XORSTR("Enabled"), &Settings::AntiAim::HeadEdge::enabled);
                }
                ImGui::NextColumn();
                {
                    ImGui::PushItemWidth(-1);
                    ImGui::SliderFloat(XORSTR("##EDGEDISTANCE"), &Settings::AntiAim::HeadEdge::distance, 20, 30, "Distance: %0.f");
                    ImGui::PopItemWidth();
                }
                ImGui::Columns(1);
                ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(210, 85));
                if (ImGui::BeginPopupModal(XORSTR("Error###UNTRUSTED_AA")))
                {
                    ImGui::Text(XORSTR("You cannot use this antiaim type on a VALVE server."));

                    ImGui::Checkbox(XORSTR("This is not a VALVE server"), &ValveDSCheck::forceUT);

                    if (ImGui::Button(XORSTR("OK")))
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
        ImGui::BeginChild(XORSTR("HVH2"), ImVec2(0, 0), true);
        {
            ImGui::Text(XORSTR("Resolver"));
            ImGui::Separator();
            ImGui::Checkbox(XORSTR("Resolve All"), &Settings::Resolver::resolveAll);
            ImGui::Separator();
            ImGui::Text(XORSTR("Movement"));
            ImGui::Checkbox(XORSTR("Auto Crouch"), &Settings::Aimbot::AutoCrouch::enabled);
            ImGui::Separator();
            ImGui::Checkbox(XORSTR("Angle Indicator"), &Settings::AngleIndicator::enabled);
            ImGui::Checkbox(XORSTR("LBY Breaker"), &Settings::AntiAim::LBYBreaker::enabled);
            if( Settings::AntiAim::LBYBreaker::enabled ){
                ImGui::SliderFloat(XORSTR("##LBYOFFSET"), &Settings::AntiAim::LBYBreaker::offset, 0, 360, "LBY Offset(from fake): %0.f");
            }
            ImGui::EndChild();
        }
    }
}
