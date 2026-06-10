#include "BubbleState.hpp"

glm::vec2 game::bubble::BubbleState::ModifyPushAmount(glm::vec2 const &normal)
{
    return normal;
}

game::bubble::BubbleState::BubbleState(BubbleComponent &owner)
    : m_owner(owner)
{
}
