#include "ShotState.hpp"

#include "FloatState.hpp"
#include "Time.hpp"
#include "Component/BubbleComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/PlatformAiMovement.hpp"
#include "Event/Sdbm.hpp"

game::BubbleStates game::bubble::ShotState::Update()
{
    if (m_timeRemaining <= 0.0f || m_owner.m_hasTrappedEnemy || m_isInWall)
    {
        return BubbleStates::Floating;
    }

    m_timeRemaining -= Time::timeDelta();

    const float direction{m_movingLeft ? -1.0f : 1.0f};
    m_owner.m_velocity = {HORIZONTAL_SPEED * direction, 0.0f};

    return BubbleStates::DoNotSwitch;
}

void game::bubble::ShotState::OnCollision(uint32_t event, dae::ColliderData const &data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (!m_owner.m_hasTrappedEnemy && data.collider->GetTag() == dae::sdbm_hash("ENEMY"))
    {
        auto &collidedEnemy{data.collider->GetGameObject()};
        collidedEnemy.GetComponent<PlatformAiMovement>()->Enabled = false;
        collidedEnemy.GetComponent<PhysicsComponent>()->Enabled = false;
        collidedEnemy.GetComponent<dae::ColliderComponent>()->Enabled = false;
        collidedEnemy.SetParent(&m_owner.GetGameObject(), false);
        collidedEnemy.SetLocalPosition({8.0f, 8.0f, 8.0f});
        collidedEnemy.SetLocalScale(0.75f);

        m_owner.m_hasTrappedEnemy = true;
    }
}

game::bubble::ShotState::ShotState(BubbleComponent &owner, bool movingLeft)
    : BubbleState(owner)
      , m_movingLeft(movingLeft)
{
}
