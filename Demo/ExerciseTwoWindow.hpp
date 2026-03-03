#ifndef MINIGIN_EXERCISETWOWINDOW_HPP
#define MINIGIN_EXERCISETWOWINDOW_HPP
#include "GuiWindow.hpp"


class ExerciseTwoWindow final : public GuiWindow
{
public:
    explicit ExerciseTwoWindow()
        : GuiWindow("Exercise 2")
    {}

private:
    int m_samples{20};

    void DrawWindowContent() override;

    void TrashCache();
};


#endif //MINIGIN_EXERCISETWOWINDOW_HPP