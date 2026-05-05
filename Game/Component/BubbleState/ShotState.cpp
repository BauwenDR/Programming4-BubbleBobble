#include "ShotState.hpp"

#include "FloatState.hpp"
#include "Time.hpp"
#include "Component/BubbleComponent.hpp"

void game::bubble::ShotState::Update()
{
    if (m_timeRemaining <= 0.0f || m_owner.m_hasTrappedEnemy || m_owner.m_isInWall)
    {
        m_owner.SwitchState(BubbleStates::Floating);
        return;
    }

    m_timeRemaining -= Time::timeDelta();

    const float direction{m_movingLeft ? -1.0f : 1.0f};
    m_owner.m_velocity = {HORIZONTAL_SPEED * direction, 0.0f};
}

bool game::bubble::ShotState::CanTrapEnemy()
{
    return true;
}

game::bubble::ShotState::ShotState(BubbleComponent &owner, bool movingLeft)
    : BubbleState(owner)
      , m_movingLeft(movingLeft)
{
}
