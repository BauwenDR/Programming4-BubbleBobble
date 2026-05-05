#include "JumpCommand.hpp"

#include "Component/PhysicsComponent.hpp"

void game::JumpCommand::Execute()
{
    m_physicsComponent->Jump();
}
