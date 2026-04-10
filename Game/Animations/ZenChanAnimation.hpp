#ifndef MINIGIN_ZENCHANANIMATION_HPP
#define MINIGIN_ZENCHANANIMATION_HPP
#include <unordered_map>

#include "AnimationData.hpp"

namespace game
{
    enum class ZenChanAnimationState
    {
        WalkingLeft,
        WalkingRight,
        WalkingLeftAngered,
        WalkingRightAngered,
    };

    const std::unordered_map<ZenChanAnimationState, AnimationData> ZENCHAN_ANIMATIONS {
        {ZenChanAnimationState::WalkingLeft, {0.0f, 0.0f, 4}},
        {ZenChanAnimationState::WalkingRight, {1.0f, 0.0f, 4}},
        {ZenChanAnimationState::WalkingLeftAngered, {2.0f, 0.0f, 4}},
        {ZenChanAnimationState::WalkingRightAngered, {3.0f, 0.0f, 4}},
    };
}

#endif //MINIGIN_ZENCHANANIMATION_HPP