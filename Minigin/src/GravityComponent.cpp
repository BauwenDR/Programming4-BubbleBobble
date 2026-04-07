#include "GravityComponent.hpp"

#include "ColliderComponent.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"
#include "Time.hpp"

void dae::GravityComponent::Start()
{
    GetGameObject().AddObserver(this);

    m_collider = GetGameObject().GetComponent<ColliderComponent>();
}

void dae::GravityComponent::Update()
{
    m_velY += GRAVITY_FORCE * Time::timeDelta();
    m_velY = std::clamp(m_velY, -TerminalVelocity, TerminalVelocity);

    glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};
    currentPos.y += m_velY * Time::timeDelta();
    GetGameObject().SetLocalPosition(currentPos);
}

void dae::GravityComponent::Notify(const GameObject &, uint32_t event, ObserverData const * data)
{
    if (event == sdbm_hash("on_collision_stay") && data != nullptr)
    {
        const auto colliderData{dynamic_cast<ColliderData const *>(data)};
        if (colliderData != nullptr && m_velY > 0)
        {
            const float newYPos{colliderData->collider->GetColliderPosition().y};

            glm::vec3 currentPos{GetGameObject().GetLocalTransform().GetPosition()};
            currentPos.y = newYPos - m_collider->GetColliderPosition().w;
            GetGameObject().SetLocalPosition(currentPos);

            m_velY = 0.0f;
            m_isOnGround = true;
        }
    }

    if (event == sdbm_hash("on_collision_exit") && data != nullptr)
    {
        m_isOnGround = false;
    }
}

void dae::GravityComponent::Jump()
{
    if (m_isOnGround)
    {
        m_velY = - 3.0f * TerminalVelocity;
        m_isOnGround = false;
    }
}
