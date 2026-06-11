#include "StaticState.hpp"

#include "Component/BubbleComponent.hpp"
#include "Event/Sdbm.hpp"

game::BubbleStates game::bubble::StaticState::Update()
{
    if (!m_owner.m_isStuckToRoof)
    {
        return BubbleStates::Floating;
    }

    return BubbleStates::DoNotChange;
}

void game::bubble::StaticState::OnCollision(uint32_t event, dae::ColliderData const &data)
{
    if (event != dae::sdbm_hash("on_collision_exit")) return;

    if (data.collider->GetTag() == dae::sdbm_hash("LEVEL_ROOF"))
    {
        m_owner.m_isStuckToRoof = false;
    }
}

glm::vec2 game::bubble::StaticState::ModifyPushAmount(glm::vec2 const &normal)
{
    return {
        m_owner.m_isInWall ? 0.0f : normal.x / 8.0f,
        std::clamp(normal.y, 0.0f, 1.0f)
    };
}

game::bubble::StaticState::StaticState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
