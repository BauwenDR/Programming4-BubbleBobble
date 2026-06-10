#include "FloatState.hpp"

#include "AirCurrentState.hpp"
#include "Component/BubbleComponent.hpp"
#include "Event/Sdbm.hpp"

game::BubbleStates game::bubble::FloatState::Update()
{
    if (m_owner.m_isInAirCurrent)
    {
        return BubbleStates::AirCurrent;
    }

    if (m_owner.m_isStuckToRoof)
    {
        return BubbleStates::Static;
    }

    m_owner.m_velocity = {0.0f, -FLOAT_SPEED};

    return BubbleStates::DoNotSwitch;
}

void game::bubble::FloatState::OnCollision(uint32_t event, const dae::ColliderData &data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (data.collider->GetTag() == dae::sdbm_hash("LEVEL_ROOF"))
    {
        m_owner.m_isStuckToRoof = true;
    }

    if (data.collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_LEFT") || data.collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_RIGHT"))
    {
        m_owner.m_isInAirCurrent = true;
        m_owner.m_isLeftCurrent = data.collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_LEFT");
    }
}

glm::vec2 game::bubble::FloatState::ModifyPushAmount(glm::vec2 const &normal)
{
    return {
        m_owner.m_isInWall ? 0.0f : normal.x * 3.0f,
        std::clamp(normal.y, 0.0f, 1.0f) * 4.0f
    };
}

game::bubble::FloatState::FloatState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
