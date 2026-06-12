#include "PhysicsComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"
#include "Time.hpp"

void game::PhysicsComponent::Start()
{
    GetGameObject().AddObserver(this);

    m_collider = GetGameObject().GetComponent<dae::ColliderComponent>();
    m_initialPosition = GetGameObject().GetLocalTransform();
}

void game::PhysicsComponent::Update()
{
    m_velY += GRAVITY_FORCE * Time::timeDelta();
    m_velY = std::clamp(m_velY, -m_jumpForce, TERMINAL_VELOCITY);

    const float drag = m_isOnGround ? DRAG_GROUND : m_velY >= 0.0f ? DRAG_AIR_FALLING : DRAG_AIR;
    m_velX /= 1.0f + drag * Time::timeDelta();

    m_velX = std::clamp(m_velX, -m_maxHorizontalSpeed, m_maxHorizontalSpeed);

    glm::vec3 currentPos{GetGameObject().GetLocalTransform().Position};
    currentPos.x += m_velX * Time::timeDelta();
    currentPos.y += m_velY * Time::timeDelta();
    GetGameObject().SetLocalPosition(currentPos);
}

void game::PhysicsComponent::LateUpdate()
{
    if (m_horizontalInput != 0.0f)
    {
        m_wasMovingLeft = m_horizontalInput < 0.0f;
    }
    m_horizontalInput = 0.0f;
}

// TODO split this function up into three private ones
// TODO also split off player specific functions
void game::PhysicsComponent::Notify(uint32_t event, dae::ObserverData const* data)
{
    if (!Enabled) return;

    if (event == dae::sdbm_hash("scene_manager_scene_switch") || event == dae::sdbm_hash("lives_changed"))
    {
        ResetToStart();
    }

    if (!(
        event == dae::sdbm_hash("on_collision_enter") ||
        event == dae::sdbm_hash("on_collision_stay") ||
        event == dae::sdbm_hash("on_collision_exit")
    ))
    {
        return;
    }

    if (data == nullptr) return;

    const auto colliderData{dynamic_cast<dae::ColliderData const*>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() == dae::sdbm_hash("BUBBLE"))
    {
        if (event == dae::sdbm_hash("on_collision_enter") && colliderData->collisionNormal.y == -1.0f)
        {
            m_onBubbleColliders.emplace(colliderData->collider);
        }
        else if (event == dae::sdbm_hash("on_collision_exit"))
        {
            m_onBubbleColliders.erase(colliderData->collider);
        }
    }

    if (colliderData->collider->GetTag() != dae::sdbm_hash("STAGE")) return;

    if (event == dae::sdbm_hash("on_collision_enter"))
    {
        const glm::vec4& ownCollider{m_collider->GetColliderPosition()};
        const glm::vec4& otherCollider{colliderData->collider->GetColliderPosition()};

        if (
            colliderData->collisionNormal.y == 1.0f ||
            ownCollider.y + ownCollider.w > otherCollider.y + otherCollider.w
        )
        {
            m_ignoredColliders.emplace(colliderData->collider);
        }

        ++m_collidingWithCount;
    }

    if (event == dae::sdbm_hash("on_collision_stay"))
    {
        // Ignore collision if we have entered it from the bottom
        if (m_ignoredColliders.contains(colliderData->collider)) return;

        if (colliderData->collisionNormal.y == 0.0f)
        {
            constexpr float epsilon{0.0001f};

            const float colliderXPos{colliderData->collider->GetColliderPosition().x};
            glm::vec3 displacementPos{GetGameObject().GetLocalTransform().Position};

            if (colliderData->collisionNormal.x > 0.0f)
            {
                displacementPos.x = colliderXPos + colliderData->collider->GetColliderPosition().z;
                if (m_horizontalInput >= 0.0f)
                {
                    displacementPos.x += epsilon;
                }

                m_velX = 0.0f;
            }
            else if (colliderData->collisionNormal.x < 0.0f)
            {
                displacementPos.x = colliderXPos - m_collider->GetColliderPosition().z;
                if (m_horizontalInput <= 0.0f)
                {
                    displacementPos.x -= epsilon;
                }

                m_velX = 0.0f;
            }

            GetGameObject().SetLocalPosition(displacementPos);
        }
        else if (m_velY > 0.0f && colliderData->collisionNormal.x == 0.0f)
        {
            const float colliderYPos{colliderData->collider->GetColliderPosition().y};
            glm::vec3 currentPos{GetGameObject().GetLocalTransform().Position};
            currentPos.y = colliderYPos - m_collider->GetColliderPosition().w;
            GetGameObject().SetLocalPosition(currentPos);

            if (!m_isOnGround)
            {
                GetGameObject().NotifyObservers(dae::sdbm_hash("has_landed"));
            }

            m_isOnGround = true;
            m_standingOn = colliderData->collider;
            m_velY = 0.0f;
        }
    }

    if (event == dae::sdbm_hash("on_collision_exit"))
    {
        --m_collidingWithCount;

        if (m_collidingWithCount <= 0)
        {
            m_collidingWithCount = 0;
            m_ignoredColliders.clear();
        }

        if (colliderData->collider == m_standingOn)
        {
            m_isOnGround = false;
            m_standingOn = nullptr;

            // When walking of an edge (not jumping) we want to slow the object down
            if (m_velY >= 0)
            {
                m_velX /= WALKING_OFF_DEVISOR;
            }
        }
    }
}

void game::PhysicsComponent::MoveHorizontal(float amount)
{
    const float accel = m_isOnGround ? m_groundAcceleration : m_airAcceleration;

    const float desiredVelX = amount * m_maxHorizontalSpeed;
    const float delta = desiredVelX - m_velX;

    const float maxChange = accel * Time::timeDelta();
    const float change = std::clamp(delta, -maxChange, maxChange);

    m_velX += change;
    m_horizontalInput += amount;
}

void game::PhysicsComponent::AirJump()
{
    m_velY = -m_jumpForce;
    m_isOnGround = false;
    GetGameObject().NotifyObservers(dae::sdbm_hash("on_jump"));
}

void game::PhysicsComponent::Jump()
{
    if ((m_isOnGround || !m_onBubbleColliders.empty()) && m_velY > 0.0f)
    {
        AirJump();
    }
}

void game::PhysicsComponent::SmallJump()
{
    m_velY = -m_jumpForce / SMALL_JUMP_DEVISOR;
    m_isOnGround = false;
    GetGameObject().NotifyObservers(dae::sdbm_hash("on_jump"));
}

void game::PhysicsComponent::ResetMovement()
{
    m_ignoredColliders.clear();
    m_collidingWithCount = 0;
    m_velX = 0.0f;
    m_velY = 0.0f;
    m_isOnGround = false;
}

void game::PhysicsComponent::ResetToStart()
{
    ResetMovement();
    GetGameObject().SetLocalPosition(m_initialPosition.Position);
    m_collider->RecalculateCollider();
}

void game::PhysicsComponent::MultiplyHorizontalSpeed(float factor)
{
    m_maxHorizontalSpeed *= factor;
}

float game::PhysicsComponent::GetXInput() const
{
    return m_horizontalInput;
}

float game::PhysicsComponent::GetVelX() const
{
    return m_velX;
}

float game::PhysicsComponent::GetVelY() const
{
    return m_velY;
}

bool game::PhysicsComponent::GetIsOnGround() const
{
    return m_isOnGround;
}

bool game::PhysicsComponent::GetWasMovingLeft() const
{
    return m_wasMovingLeft;
}
