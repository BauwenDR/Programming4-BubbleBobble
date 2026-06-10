#include "SpawnPickupOnDeath.hpp"

#include "GameObject.hpp"
#include "Prefab/Prefabs.hpp"
#include "Prefab/StagesManager.hpp"

void SpawnPickupOnDeath::OnDelete()
{
    glm::vec2 spawnPos{GetGameObject().GetWorldPosition()};
    spawnPos.y -= 8.0f;

    PickupPrefabData const pickupData{spawnPos, m_worth * PopMultiplier};
    game::StagesManager::GetInstance().SpawnPickup(pickupData);
}

SpawnPickupOnDeath::SpawnPickupOnDeath(dae::GameObject &owner, int32_t worth)
    : GameComponent(owner)
      , m_worth(worth)
{
}
