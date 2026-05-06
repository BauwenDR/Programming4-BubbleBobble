#include "AirCurrentState.hpp"

#include "Component/BubbleComponent.hpp"

void game::bubble::AirCurrentState::Update()
{
    if (!m_owner.m_isInAirCurrent)
    {
        m_owner.SwitchState(BubbleStates::Floating);
        return;
    }

    m_owner.m_velocity = {m_owner.m_isLeftCurrent ? -CURRENT_SPEED : CURRENT_SPEED, 0.0f};
}

bool game::bubble::AirCurrentState::CanTrapEnemy()
{
    return false;
}

game::bubble::AirCurrentState::AirCurrentState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
