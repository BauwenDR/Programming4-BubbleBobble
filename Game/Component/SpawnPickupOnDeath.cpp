#include "SpawnPickupOnDeath.hpp"

#include "GameObject.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/Prefabs.hpp"
#include "Prefab/StagesManager.hpp"

void game::SpawnPickupOnDeath::Start()
{
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("scene_manager_scene_switch"), this);
    m_dropEnabled = true;
}

void game::SpawnPickupOnDeath::OnDelete()
{
    dae::EventManager::GetInstance().DetachHandler(this);

    if (!m_dropEnabled) return;

    glm::vec2 spawnPos{GetGameObject().GetWorldPosition()};
    spawnPos.y -= 8.0f;

    PickupPrefabData const pickupData{spawnPos, m_worth * PopMultiplier};
    StagesManager::GetInstance().SpawnPickup(pickupData);
}

void game::SpawnPickupOnDeath::HandleEvent(uint32_t event)
{
    if (event != dae::sdbm_hash("scene_manager_scene_switch")) return;

    m_dropEnabled = false;
}

game::SpawnPickupOnDeath::SpawnPickupOnDeath(dae::GameObject &owner, int32_t worth)
    : GameComponent(owner)
      , m_worth(worth)
{
}
