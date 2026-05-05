#include "AirCurrentState.hpp"

void game::bubble::AirCurrentState::Update()
{
}

bool game::bubble::AirCurrentState::CanTrapEnemy()
{
    return false;
}

game::bubble::AirCurrentState::AirCurrentState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
