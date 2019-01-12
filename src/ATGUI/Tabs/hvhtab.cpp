#include "hvhtab.h"

#include "../../interfaces.h"
#include "../../Utils/xorstring.h"
#include "../../settings.h"
#include "../../ImGUI/imgui_internal.h"

void HvH::RenderTab()
{
	ImGui::Columns(2, NULL, true);
	{
		ImGui::BeginChild(XORSTR("HVH1"), ImVec2(0, 0), true);
		{

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

			ImGui::EndChild();
		}
	}
}
