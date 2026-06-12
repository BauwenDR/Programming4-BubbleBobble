#include "MoveCommand.hpp"

#include "Component/PhysicsComponent.hpp"

game::MoveCommand::MoveCommand(PhysicsComponent* physics, float direction)
    : m_physicsComponent(physics)
      , m_moveDirection(direction)
{
}

void game::MoveCommand::Execute()
{
    if (!m_physicsComponent->Enabled) return;

    m_physicsComponent->MoveHorizontal(m_moveDirection);
}
