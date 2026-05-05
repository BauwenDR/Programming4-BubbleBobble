#ifndef MINIGIN_PLAYERANIMATIONS_HPP
#define MINIGIN_PLAYERANIMATIONS_HPP
#include <unordered_map>

#include "AnimationData.hpp"

namespace game
{
    enum class PlayerAnimationStates : uint8_t
    {
        IdleLeft,
        IdleRight,
        WalkingLeft,
        WalkingRight,
        JumpingLeft,
        JumpingRight,
        FallingLeft,
        FallingRight,
    };

    const std::unordered_map<PlayerAnimationStates, AnimationData> PLAYER_ANIMATIONS{
        {PlayerAnimationStates::IdleLeft, {0.0f, 0.0f, 2}},
        {PlayerAnimationStates::IdleRight, {0.0f, 2.0f, 2}},
        {PlayerAnimationStates::FallingLeft, {1.0f, 0.0f, 2}},
        {PlayerAnimationStates::FallingRight, {1.0f, 2.0f, 2}},
        {PlayerAnimationStates::JumpingLeft, {2.0f, 0.0f, 2}},
        {PlayerAnimationStates::JumpingRight, {2.0f, 2.0f, 2}},
        {PlayerAnimationStates::WalkingLeft, {3.0f, 0.0f, 2}},
        {PlayerAnimationStates::WalkingRight, {3.0f, 2.0f, 2}},
    };
}

#endif //MINIGIN_PLAYERANIMATIONS_HPP
