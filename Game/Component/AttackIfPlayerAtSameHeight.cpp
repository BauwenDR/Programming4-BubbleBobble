#include "AttackIfPlayerAtSameHeight.hpp"

#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "Time.hpp"
#include "Prefab/StagesManager.hpp"

void game::AttackIfPlayerAtSameHeight::Start()
{
    m_physics = GetGameObject().GetComponent<PhysicsComponent>();
    assert(m_physics != nullptr);
}

void game::AttackIfPlayerAtSameHeight::Update()
{
    if (m_attackDelay > 0.0f)
    {
        m_attackDelay -= Time::timeDelta();
    } else
    {
        if (!m_physics->GetIsOnGround()) return;

        auto const [playerObject, _]{StagesManager::GetInstance().GetClosestActivePlayer(GetGameObject().GetWorldPosition())};

        if (std::abs(playerObject->GetWorldPosition().y - GetGameObject().GetWorldPosition().y) < 16.0f)
        {
            StagesManager::GetInstance().SpawnBoulder({GetGameObject().GetWorldPosition(), m_physics->GetWasMovingLeft()});
            m_attackDelay = ATTACK_DELAY;
        }
    }
}

game::AttackIfPlayerAtSameHeight::AttackIfPlayerAtSameHeight(dae::GameObject &owner)
    : GameComponent(owner)
{
}
