#include "StaticState.hpp"

void game::bubble::StaticState::Update()
{

}

bool game::bubble::StaticState::CanTrapEnemy()
{
    return false;
}

game::bubble::StaticState::StaticState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
