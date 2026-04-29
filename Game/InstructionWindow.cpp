#include "InstructionWindow.hpp"

#include <imgui.h>

void game::InstructionWindow::DrawWindowContent()
{
    m_showInstructions = ImGui::CollapsingHeader("Sounds:", ImGuiTreeNodeFlags_DefaultOpen);

    if (m_showInstructions)
    {
        ImGui::Text("1. Jumping");
        ImGui::Text("2. Walking over a pickup (peaches at the top of the level)");
    }

    m_showControls = ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen);

    if (m_showControls)
    {
        ImGui::Text("Gamepad: ");
        ImGui::Text("Dpad: Walk left/ walk right");
        ImGui::Text("A: Jump");
    }
}
