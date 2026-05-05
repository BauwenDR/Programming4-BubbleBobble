#include "PlatformAiMovement.hpp"

#include "Prefab/PrefabManager.hpp"

#include "Component/ColliderComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Time.hpp"

void game::PlatformAiMovement::Start()
{
    m_physics = GetGameObject().GetComponent<PhysicsComponent>();

    GetGameObject().AddObserver(this);
}

void game::PlatformAiMovement::Update()
{
    // Every 2 seconds choose a new action to undertake (moving left/ right or jumping)
    // When we are in a potential jump zone, we can jump if closest player is above us
    // When colliding with a jump collision zone, jump if closest player is not below us
    m_decisionCooldown += Time::timeDelta();
    if (m_currentAction == PlatformAiActions::None || m_decisionCooldown > DECISION_TIMEOUT)
    {
        m_decisionCooldown = std::fmod(m_decisionCooldown, DECISION_TIMEOUT);
        TakeNextMovementDecision();
    }

    switch (m_currentAction)
    {
        case PlatformAiActions::WalkingLeft:
            if (m_physics->GetVelY() - MAX_WALKING_FALLING_VELOCITY <= 0.0f)
                m_physics->MoveHorizontal(-1.0f);
            break;
        case PlatformAiActions::WalkingRight:
            if (m_physics->GetVelY() - MAX_WALKING_FALLING_VELOCITY <= 0.0f)
                m_physics->MoveHorizontal(1.0f);
            break;
        case PlatformAiActions::Jumping:
            if (std::abs(m_physics->GetVelX()) <= 1.0f && m_physics->GetIsOnGround())
                m_physics->Jump();
            break;
        case PlatformAiActions::None:
        default:
            TakeNextMovementDecision();
            m_decisionCooldown = 0.0f;
            break;
    }
}

void game::PlatformAiMovement::EdgeJump()
{
    if (std::abs(m_physics->GetVelX()) < MIN_EDGE_JUMP_SPEED) return;
    if (!m_physics->GetIsOnGround()) return;

    auto const [playerObject, _]{PrefabManager::GetInstance().GetClosestActivePlayer(GetGameObject().GetWorldPosition())};

    if (playerObject == nullptr)
    {
        return;
    }

    if (const auto &playerPos{playerObject->GetWorldPosition()}; playerPos.y <= GetGameObject().GetWorldPosition().y + 1.0f)
    {
        if (playerPos.y + JUMPING_DIFFERENCE <= GetGameObject().GetWorldPosition().y)
        {
            m_physics->Jump();
        } else
        {
            m_physics->SmallJump();
        }
        m_decisionCooldown -= DECISION_TIMEOUT;
    }
}

void game::PlatformAiMovement::InvertWalkDirection()
{
    if (m_currentAction == PlatformAiActions::WalkingLeft)
    {
        m_currentAction = PlatformAiActions::WalkingRight;
    }

    else if (m_currentAction == PlatformAiActions::WalkingRight)
    {
        m_currentAction = PlatformAiActions::WalkingLeft;
    }
}

void game::PlatformAiMovement::Notify(uint32_t event, dae::ObserverData const *data)
{
    if (event != dae::sdbm_hash("on_collision_enter") && event != dae::sdbm_hash("on_collision_exit")) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() == dae::sdbm_hash("STAGE"))
    {
        if (m_physics->GetVelY() > -1.0f && colliderData->collisionNormal.x != 0)
        {
            InvertWalkDirection();
        }

        if (colliderData->collisionNormal.y == -1.0f && m_currentAction == PlatformAiActions::Jumping)
        {
            TakeNextMovementDecision();
        }
    }

    if (event == dae::sdbm_hash("on_collision_enter"))
    {
        if (colliderData->collider->GetTag() == dae::sdbm_hash("PLATFORM_EDGE"))
        {
            EdgeJump();
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

game::PlatformAiMovement::PlatformAiMovement(dae::GameObject &owner, PlatformAiActions initialAction)
    : GameComponent(owner)
      , m_currentAction(initialAction)
{
}

void game::PlatformAiMovement::TakeNextMovementDecision()
{
    constexpr float WALKING_DECISION_DIFFERENCE{16.0f};

    auto const [playerObject, _]{PrefabManager::GetInstance().GetClosestActivePlayer(GetGameObject().GetWorldPosition())};

    if (playerObject == nullptr) return;    // TODO if both players are invulnerable, take random decisions
    const auto &playerPos{playerObject->GetWorldPosition()};
    const auto &selfPos{GetGameObject().GetWorldPosition()};

    if (m_overlappingPotentialJumpZone && playerPos.y + JUMPING_DIFFERENCE <= selfPos.y)
    {
        m_currentAction = PlatformAiActions::Jumping;
    }
    else if (m_currentAction == PlatformAiActions::Jumping || std::abs(playerPos.y - selfPos.y) <= WALKING_DECISION_DIFFERENCE)
    {
        m_currentAction = playerPos.x < selfPos.x ? PlatformAiActions::WalkingLeft : PlatformAiActions::WalkingRight;
    }
}
