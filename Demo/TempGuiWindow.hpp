#ifndef MINIGIN_TEMPGUIWINDOW_HPP
#define MINIGIN_TEMPGUIWINDOW_HPP
#include "GuiWindow.hpp"


class TempGuiWindow final : public GuiWindow
{
public:
    TempGuiWindow()
        : GuiWindow("Temp Window")
    {}

private:
    void DrawWindowContent() override;
};


#endif //MINIGIN_TEMPGUIWINDOW_HPP