#ifndef MINIGIN_CONTROLLERINPUTIMPL_HPP
#define MINIGIN_CONTROLLERINPUTIMPL_HPP
#include <memory>

#include "Input.hpp"

namespace dae
{
    class ICommand;
}

namespace dae::Input::Controller
{
    struct ControllerBinding
    {
        ControllerKey key{};
        std::size_t controllerIndex{};
        ICommand* command{};
        CommandTrigger trigger{};
    };

    class ControllerInput final
    {
    public:
        void Bind(ControllerKey key, std::size_t controllerIndex, CommandTrigger triggerType, ICommand *command) const;
        void Unbind(const ICommand *inputCommand) const;

        void Update() const;

        ControllerInput();
        ~ControllerInput();
    private:
        class Impl;
        std::unique_ptr<Impl> m_impl;
    };
}

#endif //MINIGIN_CONTROLLERINPUTIMPL_HPP