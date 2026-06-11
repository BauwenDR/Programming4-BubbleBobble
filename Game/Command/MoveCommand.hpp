#ifndef MINIGIN_MOVECOMMAND_HPP
#define MINIGIN_MOVECOMMAND_HPP

#include "Event/ICommand.hpp"

namespace game
{
    class PhysicsComponent;

    class MoveCommand final : public dae::ICommand
    {
    public:
        MoveCommand(PhysicsComponent *physics, float direction);
        void Execute() override;

    private:
        PhysicsComponent *m_physicsComponent{};
        float m_moveDirection{};
    };
}

#endif //MINIGIN_MOVECOMMAND_HPP