#include "JumpCommand.hpp"

#include "Audio/AudioQueue.hpp"
#include "Component/PhysicsComponent.hpp"

void JumpCommand::Execute()
{
    m_physicsComponent->Jump();
    dae::AudioQueue::PlaySound(1, 1.0f);
}
