#ifndef MINIGIN_MIGHTAANIMATION_HPP
#define MINIGIN_MIGHTAANIMATION_HPP
#include <cstdint>
#include <unordered_map>

#include "AnimationData.hpp"

namespace game
{
    enum class MightaAnimationStates : uint8_t
    {
        WalkingLeft,
        WalkingRight,
    };

    const std::unordered_map<MightaAnimationStates, AnimationData> MIGHTA_ANIMATIONS {
        {MightaAnimationStates::WalkingLeft, {0.0f, 0.0f, 4}},
        {MightaAnimationStates::WalkingRight, {1.0f, 0.0f, 4}},
    };
}

#endif //MINIGIN_MIGHTAANIMATION_HPP
