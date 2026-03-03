#ifndef MINIGIN_IMGUIWINDOW_HPP
#define MINIGIN_IMGUIWINDOW_HPP

#include <iostream>

class GuiWindow
{
public:
    void DrawWindow();

    virtual ~GuiWindow() = default;

protected:
    explicit GuiWindow(const std::string &windowName);

    std::string m_windowName{};
    bool m_showMenu{};
private:
    virtual void DrawWindowContent() = 0;
};


#endif //MINIGIN_IMGUIWINDOW_HPP