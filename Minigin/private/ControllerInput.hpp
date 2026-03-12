#ifndef MINIGIN_CONTROLLERINPUT_HPP
#define MINIGIN_CONTROLLERINPUT_HPP
#include "InputManager.hpp"

namespace dae::InputManager::Controller
{
    struct ControllerBinding
    {
        ControllerKey key{};
        InputCommand* command{};
        CommandTrigger trigger{};
    };

    void Initialize();

    void Bind(ControllerKey key, CommandTrigger triggerType, InputCommand *command);
    void Unbind(const InputCommand *inputCommand);

    void UpdateKeys();

    class ControllerInput
    {
    public:
        virtual ~ControllerInput() = default;
        virtual void Update() = 0;

        [[nodiscard]] uint16_t GetPressedButtons() const { return m_pressedButtons; }
        [[nodiscard]] uint16_t GetReleasedButtons() const {return m_releasedButtons; }
        [[nodiscard]] uint16_t GetHeldButtons() const { return m_heldButtons; }

    protected:
        uint16_t m_pressedButtons{};
        uint16_t m_releasedButtons{};
        uint16_t m_heldButtons{};
    };
}

#endif //MINIGIN_CONTROLLERINPUT_HPP