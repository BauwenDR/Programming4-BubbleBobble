#include "ShotState.hpp"

#include "FloatState.hpp"
#include "Time.hpp"
#include "Component/AnimationComponent.hpp"
#include "Component/BubbleComponent.hpp"
#include "Component/CapturableComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/PlatformAiMovement.hpp"
#include "Event/Sdbm.hpp"

game::BubbleStates game::bubble::ShotState::Update()
{
    if (m_timeRemaining <= 0.0f || m_owner.m_hasTrappedEnemy || m_owner.m_isInWall)
    {
        return BubbleStates::Floating;
    }

    m_timeRemaining -= Time::timeDelta();

    const float direction{m_movingLeft ? -1.0f : 1.0f};
    m_owner.m_velocity = {HORIZONTAL_SPEED * direction, 0.0f};

    return BubbleStates::DoNotChange;
}

void game::bubble::ShotState::OnCollision(uint32_t event, dae::ColliderData const &data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (!m_owner.m_hasTrappedEnemy && data.collider->GetTag() == dae::sdbm_hash("ENEMY"))
    {
        auto &collidedEnemy{data.collider->GetGameObject()};
        auto const capturable{collidedEnemy.GetComponent<CapturableComponent>()};

        if (!capturable) return;

        capturable->OnCapture();
        collidedEnemy.SetParent(&m_owner.GetGameObject(), false);
        collidedEnemy.SetLocalPosition({8.0f, 8.0f, 8.0f});

        m_owner.m_hasTrappedEnemy = true;
    }
}

game::bubble::ShotState::ShotState(BubbleComponent &owner, bool movingLeft)
    : BubbleState(owner)
      , m_movingLeft(movingLeft)
{
}
