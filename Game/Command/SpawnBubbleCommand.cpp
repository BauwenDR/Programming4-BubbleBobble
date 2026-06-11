#include "SpawnBubbleCommand.hpp"

#include "GameObject.hpp"
#include "PhysicsSystem.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/StagesManager.hpp"

void game::SpawnBubbleCommand::Execute()
{
    StagesManager::GetInstance().SpawnBubble({m_gameObject->GetWorldPosition(), m_physicsComponent->GetWasMovingLeft()});
    m_gameObject->NotifyObservers(dae::sdbm_hash("on_attack"));
}

game::SpawnBubbleCommand::SpawnBubbleCommand(dae::GameObject const *gameObject, PhysicsComponent const *physics)
    : m_gameObject(gameObject)
      , m_physicsComponent(physics)
{
}
