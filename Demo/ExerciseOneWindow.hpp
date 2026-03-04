#ifndef MINIGIN_EXERCISEONEWINDOW_HPP
#define MINIGIN_EXERCISEONEWINDOW_HPP
#include <array>
#include <vector>

#include "GuiWindow.hpp"


class ExerciseOneWindow final : public GuiWindow
{
public:
    explicit ExerciseOneWindow()
        : GuiWindow("Exercise 1")
    {
    }

private:
    constexpr static int POWERS_OF_TWO{11};
    constexpr static int BUFFER_SIZE{67108864};

    int m_samples{10};

    const std::array<int, POWERS_OF_TWO> m_x_axis{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::vector<int> m_y_axis{};

    void DrawWindowContent() override;

    void TrashCache();
};


#endif //MINIGIN_EXERCISEONEWINDOW_HPP