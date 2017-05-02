#include "triggerbottab.h"

void Triggerbot::RenderTab()
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
				if (!Settings::Triggerbot::Delay::enabled)
				{
					ImGui::PushItemWidth(-1);
					ImGui::Checkbox("Random", &Settings::Triggerbot::RandomDelay::enabled);
					SetTooltip("Adds a random delay to your Triggerbot");
				}
				if (!Settings::Triggerbot::RandomDelay::enabled)
				{
					ImGui::PushItemWidth(-1);
					ImGui::Checkbox("Custom", &Settings::Triggerbot::Delay::enabled);
					SetTooltip("Adds a custom delay to the Triggerbot");
				}
			}
			ImGui::NextColumn();
			{
				if (Settings::Triggerbot::Delay::enabled)
				{
					ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##TRIGGERDELAY", &Settings::Triggerbot::Delay::value, 0, 1000);
					ImGui::PopItemWidth();
				}
				else
				if (Settings::Triggerbot::RandomDelay::enabled)
				{
					ImGui::PushItemWidth(-1);
					ImGui::SliderInt("##RANDTRIGGERMIN", &Settings::Triggerbot::RandomDelay::min, 0, 999, "MIN: %0.3f");
					ImGui::SliderInt("##RANDTRIGGERMAX", &Settings::Triggerbot::RandomDelay::max, 1, 1000, "MAX: %0.3f");
				}

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