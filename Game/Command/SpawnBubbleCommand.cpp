#include "SpawnBubbleCommand.hpp"

#include "GameObject.hpp"
#include "PhysicsSystem.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/StagesManager.hpp"

void game::SpawnProjectileCommand::Execute()
{
    ProjectilePrefabData const data{m_gameObject->GetWorldPosition(), m_physicsComponent->GetWasMovingLeft()};

    if (m_isBoulder)
    {
        StagesManager::GetInstance().SpawnBoulder(data);
    } else
    {
        StagesManager::GetInstance().SpawnBubble(data);
    }

    m_gameObject->NotifyObservers(dae::sdbm_hash("on_attack"));
}

game::SpawnProjectileCommand::SpawnProjectileCommand(dae::GameObject const *gameObject, PhysicsComponent const *physics, bool m_isBoulder)
    : m_gameObject(gameObject)
      , m_physicsComponent(physics)
      , m_isBoulder(m_isBoulder)
{
}
