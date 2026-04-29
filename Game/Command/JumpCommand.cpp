#include "JumpCommand.hpp"

#include "Component/PhysicsComponent.hpp"

void JumpCommand::Execute()
{
    m_physicsComponent->Jump();
}
