#ifndef MINIGIN_CONTROLLERINPUT_HPP
#define MINIGIN_CONTROLLERINPUT_HPP
#include <SDL3/SDL_gamepad.h>

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

        uint16_t GetPressedButtons() const { return m_pressedButtons; }
        uint16_t GetReleasedButtons() const {return m_releasedButtons; }
        uint16_t GetHeldButtons() const { return m_heldButtons; }

    protected:
        uint16_t m_pressedButtons{};
        uint16_t m_releasedButtons{};
        uint16_t m_heldButtons{};
    };

#if _WIN32 or _WIN64
    class XControllerInput final : public ControllerInput
    {
    public:
        void Update() override;

        ~XControllerInput() override = default;
    };
#endif

    class SDLControllerInput final : public ControllerInput
    {
    public:
        SDLControllerInput();
        void Update() override;

        ~SDLControllerInput() override;

    private:
        SDL_Gamepad *m_pGamepad{};
    };
}

#endif //MINIGIN_CONTROLLERINPUT_HPP