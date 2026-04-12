#include "PlatformAiMovement.hpp"

#include "Time.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"

void game::PlatformAiMovement::Start()
{
    m_physics = GetGameObject().GetComponent<dae::PhysicsComponent>();
}

void game::PlatformAiMovement::Update()
{
    // Every 2 seconds choose a new action to undertake (moving left/ right or jumping)
    // When we are in a potential jump zone, we can jump if closest player is above us
    // When colliding with a jump collision zone, jump if closest player is not below us

    m_decisionCooldown += Time::timeDelta();
    if (m_currentAction == PlatformAiAction::None || m_decisionCooldown > DECISION_TIMEOUT)
    {
        m_decisionCooldown = std::fmod(m_decisionCooldown, DECISION_TIMEOUT);
        TakeNextMovementDecision();
    }

    if (m_overlappingJumpZone)
    {

    }

    switch (m_currentAction)
    {
        case PlatformAiAction::WalkingLeft:
            m_physics->MoveHorizontal(-1.0f);
            break;
        case PlatformAiAction::WalkingRight:
            m_physics->MoveHorizontal(1.0f);
            break;
        case PlatformAiAction::Jumping:
            m_physics->Jump();
            break;
        case PlatformAiAction::None:
        default:
            TakeNextMovementDecision();
            m_decisionCooldown = 0.0f;
            break;
    }
}

void game::PlatformAiMovement::Notify(uint32_t event, dae::ObserverData const *data)
{
    if (event != dae::sdbm_hash("on_collision_enter") && event != dae::sdbm_hash("on_collision_exit")) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (event == dae::sdbm_hash("on_collision_enter"))
    {

    }

    if (event == dae::sdbm_hash("on_collision_exit"))
    {

    }
}

game::PlatformAiMovement::PlatformAiMovement(dae::GameObject &owner)
    : GameComponent(owner)
{
}

void game::PlatformAiMovement::TakeNextMovementDecision()
{
    m_currentAction = PlatformAiAction::WalkingLeft;
}
