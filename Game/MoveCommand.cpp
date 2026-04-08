#include "MoveCommand.hpp"

#include "Component/PhysicsComponent.hpp"

game::MoveCommand::MoveCommand(dae::PhysicsComponent *physics, float direction)
  : m_physicsComponent(physics)
    , m_moveDirection(direction)
{
}

void game::MoveCommand::Execute()
{
  m_physicsComponent->MoveHorizontal(m_moveDirection);
}
