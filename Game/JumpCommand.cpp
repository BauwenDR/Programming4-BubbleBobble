#include "JumpCommand.hpp"

#include "PhysicsComponent.hpp"

void JumpCommand::Execute()
{
    m_physicsComponent->Jump();
}
