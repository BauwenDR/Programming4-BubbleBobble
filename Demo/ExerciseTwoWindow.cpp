#include "ExerciseTwoWindow.hpp"

#include <imgui.h>

void ExerciseTwoWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache"))
    {
        TrashCache();
        std::cout << m_samples << "\n";
    }
}

void ExerciseTwoWindow::TrashCache()
{
}
