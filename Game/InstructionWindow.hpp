#ifndef MINIGIN_INSTRUCTIONWINDOW_HPP
#define MINIGIN_INSTRUCTIONWINDOW_HPP
#include "Render/GuiWindow.hpp"

namespace game
{
    class InstructionWindow final : public dae::GuiWindow
    {
    public:
        explicit InstructionWindow() : GuiWindow("Instructions") {}

    private:
        bool m_showInstructions{true};
        bool m_showControls{true};

        void DrawWindowContent() override;
    };
}

#endif //MINIGIN_INSTRUCTIONWINDOW_HPP
