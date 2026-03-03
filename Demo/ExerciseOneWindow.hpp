#ifndef MINIGIN_EXERCISEONEWINDOW_HPP
#define MINIGIN_EXERCISEONEWINDOW_HPP
#include "GuiWindow.hpp"


class ExerciseOneWindow final : public GuiWindow
{
public:
    explicit ExerciseOneWindow()
        : GuiWindow("Exercise 1")
    {
    }

private:
    int m_samples{10};

    void DrawWindowContent() override;

    void TrashCache();
};


#endif //MINIGIN_EXERCISEONEWINDOW_HPP