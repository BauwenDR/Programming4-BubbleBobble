#include "PhysicsComponent.hpp"

#include "ColliderComponent.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"
#include "Time.hpp"

void dae::PhysicsComponent::Start()
{
    GetGameObject().AddObserver(this);

    m_collider = GetGameObject().GetComponent<ColliderComponent>();
}

void dae::PhysicsComponent::Update()
{
    m_velY += GRAVITY_FORCE * Time::timeDelta();
    m_velY = std::clamp(m_velY, -JUMP_FORCE, TERMINAL_VELOCITY);

    const float drag = m_isOnGround ? m_dragGround : m_dragAir;
    m_velX /= 1.0f + drag * Time::timeDelta();

    const float maxSpeed = m_isOnGround ? m_maxSpeedGround : m_maxSpeedAir;
    m_velX = std::clamp(m_velX, -maxSpeed, maxSpeed);

    glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};
    currentPos.x += m_velX * Time::timeDelta();
    currentPos.y += m_velY * Time::timeDelta();
    GetGameObject().SetLocalPosition(currentPos);
}

void dae::PhysicsComponent::Notify(const GameObject &, uint32_t event, ObserverData const *data)
{
    const auto colliderData{dynamic_cast<ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    constexpr float epsilon{0.001};
    if (event == sdbm_hash("on_collision_enter"))
    {
        (*m_collidingWith)[colliderData->collider] =
                colliderData->collisionNormal.y == 1.0f &&
                colliderData->collider->GetColliderPosition().w <= MAX_JUMP_THROUGH_HEIGHT;
    }
    if (event == sdbm_hash("on_collision_stay") && data != nullptr)
    {
        // Ignore collision if we entered it from the bottom
        if (!m_collidingWith->contains(colliderData->collider) || (*m_collidingWith)[colliderData->collider]) return;

        if (colliderData->collisionNormal.y == 0.0f)
        {
            const float colliderXPos{colliderData->collider->GetColliderPosition().x};
            glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};

            if (colliderData->collisionNormal.x > 0.0f)
            {
                currentPos.x = colliderXPos + colliderData->collider->GetColliderPosition().z + epsilon;
                m_velX = 0.0f;
            } else
            {
                currentPos.x = colliderXPos - m_collider->GetColliderPosition().z - epsilon;
                m_velX = 0.0f;
            }

            GetGameObject().SetLocalPosition(currentPos);
        }else if (m_velY > 0 && colliderData->collisionNormal.x == 0)
        {
            const float colliderYPos{colliderData->collider->GetColliderPosition().y};
            glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};
            currentPos.y = colliderYPos - m_collider->GetColliderPosition().w;
            GetGameObject().SetLocalPosition(currentPos);

            m_isOnGround = true;
            m_standingOn = colliderData->collider;
            m_velY = 0.0f;
        }
    }

    if (event == sdbm_hash("on_collision_exit") && data != nullptr)
    {
        m_collidingWith->erase(colliderData->collider);

        if (colliderData->collider == m_standingOn)
        {
            m_isOnGround = false;
            m_standingOn = nullptr;
        }
    }
}

void dae::PhysicsComponent::MoveHorizontal(float amount)
{
    const float accel = m_isOnGround ? m_accelGround : m_accelAir;
    const float maxSpeed = m_isOnGround ? m_maxSpeedGround : m_maxSpeedAir;

    // accelerate towards desired velocity
    const float desiredVelX = amount * maxSpeed;
    const float delta = desiredVelX - m_velX;
    // Apply acceleration (clamp change by accel * dt)
    const float maxChange = accel * Time::timeDelta();
    const float change = std::clamp(delta, -maxChange, maxChange);
    m_velX += change;
}

void dae::PhysicsComponent::Jump()
{
    if (m_isOnGround)
    {
        m_velY = -JUMP_FORCE;
        m_isOnGround = false;
    }
}
