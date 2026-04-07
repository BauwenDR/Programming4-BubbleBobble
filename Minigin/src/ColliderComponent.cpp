#include "ColliderComponent.hpp"

void dae::ColliderComponent::OnCollisionEnter(ColliderComponent const *collider) const
{
    const ColliderData data{collider};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_enter"), &data);
}

void dae::ColliderComponent::OnCollisionStay(ColliderComponent const *collider) const
{
    const ColliderData data{collider};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_stay"), &data);
}

void dae::ColliderComponent::OnCollisionExit(ColliderComponent const *collider) const
{
    const ColliderData data{collider};
    GetGameObject().NotifyObservers(sdbm_hash("on_collision_exit"), &data);
}

bool dae::ColliderComponent::Intersects(const ColliderComponent &colliderComponent) const
{
    const auto r1{m_collider};
    const auto r2{colliderComponent.m_collider};

    // If one rectangle is on left side of the other
    if (r1.x + r1.z < r2.x || r2.x + r2.z < r1.x)
    {
        return false;
    }

    // If one rectangle is under the other
    if (r1.y > r2.y + r2.w || r2.y > r1.y + r1.w)
    {
        return false;
    }

    return true;
}

void dae::ColliderComponent::Start()
{
    m_collider.x = GetGameObject().GetWorldPosition().x;
    m_collider.y = GetGameObject().GetWorldPosition().y;
}

void dae::ColliderComponent::Update()
{
    m_collider.x = GetGameObject().GetWorldPosition().x;
    m_collider.y = GetGameObject().GetWorldPosition().y;
}
