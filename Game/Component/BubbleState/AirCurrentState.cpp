#include "AirCurrentState.hpp"

#include "Component/BubbleComponent.hpp"
#include "Event/Sdbm.hpp"

game::BubbleStates game::bubble::AirCurrentState::Update()
{
    if (!m_owner.m_isInAirCurrent)
    {
        return BubbleStates::Floating;
    }

    m_owner.m_velocity = {m_owner.m_isLeftCurrent ? -CURRENT_SPEED : CURRENT_SPEED, 0.0f};

    return BubbleStates::DoNotChange;
}

void game::bubble::AirCurrentState::OnCollision(uint32_t event, const dae::ColliderData &data)
{
    if (event != dae::sdbm_hash("on_collision_exit")) return;

    if (data.collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_LEFT") || data.collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_RIGHT"))
    {
        m_owner.m_isInAirCurrent = false;
    }
}

game::bubble::AirCurrentState::AirCurrentState(BubbleComponent &owner)
    : BubbleState(owner)
{
}
