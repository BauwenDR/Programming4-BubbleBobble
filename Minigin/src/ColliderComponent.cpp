#include "ColliderComponent.hpp"

#include "Sdbm.hpp"

void dae::ColliderComponent::OnCollisionEnter(ColliderComponent const *collider, glm::vec2 const & normal) const
{
    const ColliderData data{collider, normal};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_enter"), &data);
}

void dae::ColliderComponent::OnCollisionStay(ColliderComponent const *collider, glm::vec2 const & normal) const
{
    const ColliderData data{collider, normal};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_stay"), &data);
}

void dae::ColliderComponent::OnCollisionExit(ColliderComponent const *collider) const
{
    const ColliderData data{collider, {}};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_exit"), &data);
}

void dae::ColliderComponent::Start()
{
    RecalculateCollider();
}

void dae::ColliderComponent::Update()
{
    RecalculateCollider();
}

void dae::ColliderComponent::RecalculateCollider()
{
    m_collider.x = GetGameObject().GetWorldPosition().x;
    m_collider.y = GetGameObject().GetWorldPosition().y;

    m_center.x = m_collider.x + m_collider.z / 2.0f;
    m_center.y = m_collider.y + m_collider.w / 2.0f;
}
