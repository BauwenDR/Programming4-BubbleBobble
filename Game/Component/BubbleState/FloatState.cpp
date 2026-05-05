#include "FloatState.hpp"

#include "AirCurrentState.hpp"
#include "Component/BubbleComponent.hpp"

void game::bubble::FloatState::Update()
{
    if (m_owner.m_isInAirCurrent)
    {
        m_owner.SwitchState(BubbleStates::AirCurrent);
        return;
    }

    if (m_owner.m_isStuckToRoof)
    {
        m_owner.SwitchState(BubbleStates::Static);
        return;
    }

    m_owner.m_velocity = {0.0f, -FLOAT_SPEED};
}

bool game::bubble::FloatState::CanTrapEnemy()
{
    return false;
}

game::bubble::FloatState::FloatState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
