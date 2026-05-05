#ifndef MINIGIN_JUMPCOMMAND_HPP
#define MINIGIN_JUMPCOMMAND_HPP
#include "Event/ICommand.hpp"

namespace game
{
    class PhysicsComponent;

    class JumpCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        explicit JumpCommand(PhysicsComponent *physics) : m_physicsComponent(physics) {}
        ~JumpCommand() override = default;
    private:
        PhysicsComponent *m_physicsComponent;
    };
}

#endif //MINIGIN_JUMPCOMMAND_HPP