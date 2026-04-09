#ifndef MINIGIN_MOVECOMMAND_HPP
#define MINIGIN_MOVECOMMAND_HPP

#include "Event/ICommand.hpp"

namespace dae
{
    class PhysicsComponent;
}

namespace game
{
    class MoveCommand final : public dae::ICommand
    {
    public:
        MoveCommand(dae::PhysicsComponent *physics, float direction);
        void Execute() override;

    private:
        dae::PhysicsComponent *m_physicsComponent{};
        float m_moveDirection{};
    };
}

#endif //MINIGIN_MOVECOMMAND_HPP