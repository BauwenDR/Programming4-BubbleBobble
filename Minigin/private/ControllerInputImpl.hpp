#ifndef MINIGIN_CONTROLLERINPUTIMPL_HPP
#define MINIGIN_CONTROLLERINPUTIMPL_HPP
#include "ControllerInput.hpp"

#if not (_WIN32 or _WIN64)
#include <SDL3/SDL_gamepad.h>
#endif

namespace dae::InputManager::Controller
{
    class ControllerInputImpl final : public ControllerInput
    {
    public:
        ControllerInputImpl();
        void Update() override;

        ~ControllerInputImpl() override;

    private:
#if not (_WIN32 or _WIN64)
        SDL_Gamepad *m_pGamepad{};
#endif
    };
}

#endif //MINIGIN_CONTROLLERINPUTIMPL_HPP