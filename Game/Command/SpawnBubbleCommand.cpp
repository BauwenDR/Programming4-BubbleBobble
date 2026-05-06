#include "SpawnBubbleCommand.hpp"

#include "GameObject.hpp"
#include "PhysicsSystem.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/PrefabManager.hpp"

void SpawnBubbleCommand::Execute()
{
    game::PrefabManager::GetInstance().SpawnBubble({m_gameObject->GetWorldPosition(), m_physicsComponent->GetWasMovingLeft()});
    m_gameObject->NotifyObservers(dae::sdbm_hash("on_attack"));
}

SpawnBubbleCommand::SpawnBubbleCommand(dae::GameObject const *gameObject, game::PhysicsComponent const *physics)
    : m_gameObject(gameObject)
      , m_physicsComponent(physics)
{
}
