#include "StaticState.hpp"

#include "Component/BubbleComponent.hpp"

void game::bubble::StaticState::Update()
{
    if (!m_owner.m_isStuckToRoof)
    {
        m_owner.SwitchState(BubbleStates::Floating);
    }
}

bool game::bubble::StaticState::CanTrapEnemy()
{
    return false;
}

game::bubble::StaticState::StaticState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
