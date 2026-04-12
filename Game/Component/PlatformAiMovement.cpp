#include "PlatformAiMovement.hpp"

#include "Time.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/PrefabManager.hpp"

void game::PlatformAiMovement::Start()
{
    m_physics = GetGameObject().GetComponent<dae::PhysicsComponent>();

    GetGameObject().AddObserver(this);
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

    switch (m_currentAction)
    {
        case PlatformAiAction::WalkingLeft:
            if (m_physics->GetVelY() - MAX_WALKING_FALLING_VELOCITY <= 0.0f)
                m_physics->MoveHorizontal(-1.0f);
            break;
        case PlatformAiAction::WalkingRight:
            if (m_physics->GetVelY() - MAX_WALKING_FALLING_VELOCITY <= 0.0f)
                m_physics->MoveHorizontal(1.0f);
            break;
        case PlatformAiAction::Jumping:
            if (std::abs(m_physics->GetVelX()) <= 1.0f)
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

    if (colliderData->collider->GetTag() == dae::sdbm_hash("STAGE") && colliderData->collisionNormal.x != 0)
    {
        if (m_currentAction == PlatformAiAction::WalkingLeft)
        {
            m_currentAction = PlatformAiAction::WalkingRight;
        }

        else if (m_currentAction == PlatformAiAction::WalkingRight)
        {
            m_currentAction = PlatformAiAction::WalkingLeft;
        }
    }

    if (colliderData->collider->GetTag() == dae::sdbm_hash("STAGE") && colliderData->collisionNormal.y != 0)
    {
        TakeNextMovementDecision();
    }

    if (event == dae::sdbm_hash("on_collision_enter"))
    {
        if (std::abs(m_physics->GetVelX()) > MIN_EDGE_JUMP_SPEED && colliderData->collider->GetTag() == dae::sdbm_hash("PLATFORM_EDGE"))
        {
            auto const [playerObject, _]{PrefabManager::GetInstance().GetClosestActivePlayer(GetGameObject().GetWorldPosition())};

            if (playerObject == nullptr) return;

            if (const auto &playerPos{playerObject->GetWorldPosition()}; playerPos.y <= GetGameObject().GetWorldPosition().y + 1.0f)
            {
                if (playerPos.y - JUMPING_DIFFERENCE <= GetGameObject().GetWorldPosition().y)
                {
                    m_physics->Jump();
                } else
                {
                    m_physics->SmallJump();
                }
                m_decisionCooldown -= DECISION_TIMEOUT;
            }
        }
        else if (colliderData->collider->GetTag() == dae::sdbm_hash("AI_JUMPABLE"))
        {
            m_overlappingPotentialJumpZone = true;
        }
    }

    if (event == dae::sdbm_hash("on_collision_exit"))
    {
        if (colliderData->collider->GetTag() == dae::sdbm_hash("AI_JUMPABLE"))
        {
            m_overlappingPotentialJumpZone = false;
        }
    }
}

game::PlatformAiMovement::PlatformAiMovement(dae::GameObject &owner, PlatformAiAction initialAction)
    : GameComponent(owner)
      , m_currentAction(initialAction)
{
}

void game::PlatformAiMovement::TakeNextMovementDecision()
{
    constexpr float WALKING_DECISION_DIFFERENCE{32.0f};

    auto const [playerObject, _]{PrefabManager::GetInstance().GetClosestActivePlayer(GetGameObject().GetWorldPosition())};

    if (playerObject == nullptr) return;
    const auto &playerPos{playerObject->GetWorldPosition()};
    const auto &selfPos{GetGameObject().GetWorldPosition()};

    if (m_currentAction == PlatformAiAction::Jumping || std::abs(playerPos.y - selfPos.y) <= WALKING_DECISION_DIFFERENCE)
    {
        m_currentAction = playerPos.x < selfPos.x ? PlatformAiAction::WalkingLeft : PlatformAiAction::WalkingRight;
    }
    else if (m_overlappingPotentialJumpZone && playerPos.y - JUMPING_DIFFERENCE <= selfPos.y)
    {
        m_currentAction = PlatformAiAction::Jumping;
    }
}
