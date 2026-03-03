#include "ExerciseOneWindow.hpp"

#include <imgui.h>

void ExerciseOneWindow::DrawWindowContent()
{
    ImGui::InputInt("Samples", &m_samples);
    if (ImGui::Button("Thrash the cache"))
    {
        TrashCache();
        std::cout << m_samples << "\n";
    }
}

void ExerciseOneWindow::TrashCache()
{
}
