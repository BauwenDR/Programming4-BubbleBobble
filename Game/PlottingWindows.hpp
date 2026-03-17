#ifndef MINIGIN_PLOTTINGWINDOWS_HPP
#define MINIGIN_PLOTTINGWINDOWS_HPP

#include <array>
#include <vector>

#include "GuiWindow.hpp"

namespace game
{
    class ExerciseOneWindow final : public dae::GuiWindow
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
    };

    class ExerciseTwoWindow final : public dae::GuiWindow
    {
    public:
        explicit ExerciseTwoWindow()
            : GuiWindow("Exercise 2")
        {}

    private:
        constexpr static int BUFFER_SIZE{1048576};
        constexpr static int POWERS_OF_TWO{11};

        int m_samples{20};

        const std::array<int, POWERS_OF_TWO> m_xAxis{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
        std::vector<int> m_smallYAxis{};
        std::vector<int> m_bigYAxis{};

        void DrawWindowContent() override;
    };
}

#endif //MINIGIN_PLOTTINGWINDOWS_HPP