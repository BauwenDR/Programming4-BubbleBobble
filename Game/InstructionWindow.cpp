#include "InstructionWindow.hpp"

#include <imgui.h>

void game::InstructionWindow::DrawWindowContent()
{
    ImGui::Text("Basic Bubble Bobble recreation");
    ImGui::Text("Trap enemies with your bubbles");
    ImGui::Text("Score is rewarded when a bubble is popped");
    ImGui::Text("In order to pop a bubble, hit it vertically");

    m_showInstructions = ImGui::CollapsingHeader("Sounds:", ImGuiTreeNodeFlags_DefaultOpen);
    if (m_showInstructions)
    {
        ImGui::Text("1. Jumping");
        ImGui::Text("2. Walking over a pickup (peaches at the top of the level)");
        ImGui::Text("3. Shooting");
    }

    m_showControls = ImGui::CollapsingHeader("Controls", ImGuiTreeNodeFlags_DefaultOpen);
    if (m_showControls)
    {
        ImGui::Text("Gamepad: ");
        ImGui::Text("Dpad: Walk left/ walk right");
        ImGui::Text("A: Jump");
        ImGui::Text("X: Shoot");
    }

    m_showStateMachine = ImGui::CollapsingHeader("StateMachine", ImGuiTreeNodeFlags_DefaultOpen);
    if (m_showStateMachine)
    {
        ImGui::Text("The bubbles are controlled using a state");
        ImGui::Text("They start out as shot");
        ImGui::Text("From there, they can either fly up");
        ImGui::Text("Or Get stuck against a roof");
    }
}
