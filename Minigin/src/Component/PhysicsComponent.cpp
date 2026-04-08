#include "Component/PhysicsComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"
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

    const float drag = m_isOnGround ? DRAG_GROUND : m_velY >= 0.0f ? DRAG_AIR_FALLING : DRAG_AIR;
    m_velX /= 1.0f + drag * Time::timeDelta();

    m_velX = std::clamp(m_velX, -m_maxHorizontalSpeed, m_maxHorizontalSpeed);

    glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};
    currentPos.x += m_velX * Time::timeDelta();
    currentPos.y += m_velY * Time::timeDelta();
    GetGameObject().SetLocalPosition(currentPos);
}

void dae::PhysicsComponent::Notify(const GameObject &, uint32_t event, ObserverData const *data)
{
    const auto colliderData{dynamic_cast<ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() != sdbm_hash("STAGE")) return;

    if (event == sdbm_hash("on_collision_enter"))
    {
        const glm::vec4 &ownCollider{m_collider->GetColliderPosition()};
        const glm::vec4 &otherCollider{colliderData->collider->GetColliderPosition()};

        if (
            colliderData->collisionNormal.y == 1.0f ||
            ownCollider.y + ownCollider.w > otherCollider.y + otherCollider.w
        )
        {
            m_ignoredCollider = colliderData->collider;
        };
    }
    if (event == sdbm_hash("on_collision_stay") && data != nullptr)
    {
        // Ignore collision if we have entered it from the bottom
        if (m_ignoredCollider == colliderData->collider) return;

        if (colliderData->collisionNormal.y == 0.0f)
        {
            constexpr float epsilon{0.001f};

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
        } else if (m_velY > 0.0f && colliderData->collisionNormal.x == 0.0f)
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
        if (m_ignoredCollider == colliderData->collider)
        {
            m_ignoredCollider = nullptr;
        }

        if (colliderData->collider == m_standingOn)
        {
            m_isOnGround = false;
            m_standingOn = nullptr;

            if (m_velY >= 0)
            {
                m_velX /= WALKING_OFF_DEVISOR;
            }
        }
    }
}

void dae::PhysicsComponent::MoveHorizontal(float amount)
{
    const float accel = m_isOnGround ? ACCELERATION_GROUND : ACCELERATION_AIR;

    const float desiredVelX = amount * m_maxHorizontalSpeed;
    const float delta = desiredVelX - m_velX;

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
