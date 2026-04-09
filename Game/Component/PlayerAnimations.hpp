#ifndef MINIGIN_PLAYERANIMATIONS_HPP
#define MINIGIN_PLAYERANIMATIONS_HPP
#include <unordered_map>

namespace game
{
    enum class PlayerAnimationState
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

    struct AnimationData
    {
        float row;
        float col;
        int frames;
    };

    const std::unordered_map<PlayerAnimationState, AnimationData> PLAYER_ANIMATIONS{
        {PlayerAnimationState::IdleLeft, {0.0f, 0.0f, 2}},
        {PlayerAnimationState::IdleRight, {0.0f, 2.0f, 2}},
        {PlayerAnimationState::FallingLeft, {1.0f, 0.0f, 2}},
        {PlayerAnimationState::FallingRight, {1.0f, 2.0f, 2}},
        {PlayerAnimationState::JumpingLeft, {2.0f, 0.0f, 2}},
        {PlayerAnimationState::JumpingRight, {2.0f, 2.0f, 2}},
        {PlayerAnimationState::WalkingLeft, {3.0f, 0.0f, 2}},
        {PlayerAnimationState::WalkingRight, {3.0f, 2.0f, 2}},
    };
}

#endif //MINIGIN_PLAYERANIMATIONS_HPP
