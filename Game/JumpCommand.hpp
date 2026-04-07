#ifndef MINIGIN_JUMPCOMMAND_HPP
#define MINIGIN_JUMPCOMMAND_HPP
#include "ICommand.hpp"


namespace dae
{
        class PhysicsComponent;
}

class JumpCommand final : public dae::ICommand
{
public:
        void Execute() override;

        JumpCommand(dae::PhysicsComponent *physics) : m_physicsComponent(physics) {}
        ~JumpCommand() override = default;
private:
        dae::PhysicsComponent *m_physicsComponent;
};


#endif //MINIGIN_JUMPCOMMAND_HPP