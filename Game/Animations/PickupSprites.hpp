#ifndef MINIGIN_PICKUPSPRITES_HPP
#define MINIGIN_PICKUPSPRITES_HPP
#include <cstdint>
#include <unordered_map>

#include <glm/vec2.hpp>

namespace game
{
    const std::unordered_map<int32_t, glm::vec2> PICKUP_SPRITE_OFFSETS {
        {100, glm::vec2(2.0f, 0.0f)},
        {200, glm::vec2(2.0f, 2.0f)},
        {400, glm::vec2(2.0f, 1.0f)},
        {800, glm::vec2(0.0f, 0.0f)},
        {1600, glm::vec2(0.0f, 1.0f)},
        {3200, glm::vec2(0.0f, 2.0f)},
    };
}

#endif //MINIGIN_PICKUPSPRITES_HPP
