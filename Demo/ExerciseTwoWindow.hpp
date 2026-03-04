#ifndef MINIGIN_EXERCISETWOWINDOW_HPP
#define MINIGIN_EXERCISETWOWINDOW_HPP
#include <array>
#include <vector>

#include "GuiWindow.hpp"


class ExerciseTwoWindow final : public GuiWindow
{
public:
    explicit ExerciseTwoWindow()
        : GuiWindow("Exercise 2")
    {}

private:
    constexpr static int BUFFER_SIZE{67108864};
    constexpr static int POWERS_OF_TWO{11};

    int m_samples{20};

    const std::array<int, POWERS_OF_TWO> m_xAxis{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    const std::array<int, POWERS_OF_TWO> m_x_axis_2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    std::vector<int> m_smallYAxis{};
    std::vector<int> m_bigYAxis{};

    void DrawWindowContent() override;

    void TrashCacheBig();
    void TrashCacheSmall();
};


#endif //MINIGIN_EXERCISETWOWINDOW_HPP