#include "JumpCommand.hpp"

#include "Audio/AudioQueue.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"

void JumpCommand::Execute()
{
    m_physicsComponent->Jump();
    dae::AudioQueue::PlaySound(dae::sdbm_hash("PlayerJump"), 1.0f);
}
