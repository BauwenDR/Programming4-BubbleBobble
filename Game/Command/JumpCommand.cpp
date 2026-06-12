#include "JumpCommand.hpp"

#include "Component/PhysicsComponent.hpp"

void game::JumpCommand::Execute()
{
    if (!m_physicsComponent->Enabled) return;

    m_physicsComponent->Jump();
}
