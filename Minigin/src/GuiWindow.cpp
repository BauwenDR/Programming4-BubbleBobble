#include "GuiWindow.hpp"

#include <imgui.h>

void GuiWindow::DrawWindow()
{
    ImGui::Begin(m_windowName.c_str(), &m_showMenu);

    DrawWindowContent();

    ImGui::End();
}

GuiWindow::GuiWindow(const std::string &windowName)
    : m_windowName(windowName)
{
}
