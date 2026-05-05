#ifndef MINIGIN_ZENCHANANIMATION_HPP
#define MINIGIN_ZENCHANANIMATION_HPP
#include <unordered_map>

#include "AnimationData.hpp"

namespace game
{
    enum class ZenChanAnimationStates : uint8_t
    {
        WalkingLeft,
        WalkingRight,
        WalkingLeftAngered,
        WalkingRightAngered,
    };

    const std::unordered_map<ZenChanAnimationStates, AnimationData> ZEN_CHAN_ANIMATIONS {
        {ZenChanAnimationStates::WalkingLeft, {0.0f, 0.0f, 4}},
        {ZenChanAnimationStates::WalkingRight, {1.0f, 0.0f, 4}},
        {ZenChanAnimationStates::WalkingLeftAngered, {2.0f, 0.0f, 4}},
        {ZenChanAnimationStates::WalkingRightAngered, {3.0f, 0.0f, 4}},
    };
}

#endif //MINIGIN_ZENCHANANIMATION_HPP