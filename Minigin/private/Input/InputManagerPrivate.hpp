#ifndef MINIGIN_INPUTMANAGERPRIVATE_HPP
#define MINIGIN_INPUTMANAGERPRIVATE_HPP

#include "Event/ICommand.hpp"
#include "Input/Input.hpp"

namespace dae::Input
{
    void Init();

    void ExecuteIfTriggerMatch(const auto binding, CommandTrigger commandTrigger)
    {
        // Extract some names into local variables for easier to read code
        const auto &trigger{binding->trigger};
        const auto &command{binding->command};

        if (trigger == commandTrigger)
        {
            command->Execute();
        }
    }
}

#endif //MINIGIN_INPUTMANAGERPRIVATE_HPP