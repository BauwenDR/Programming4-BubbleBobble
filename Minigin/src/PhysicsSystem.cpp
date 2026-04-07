#include "PhysicsSystem.hpp"

#include <algorithm>

#include "ColliderComponent.hpp"

void dae::PhysicsSystem::RegisterCollider(ColliderComponent *collider)
{
    m_colliders.push_back(collider);
}

void dae::PhysicsSystem::UnregisterCollider(ColliderComponent *collider)
{
    std::ranges::remove_if(m_colliders, [collider](ColliderComponent const * colliderComp)
    {
        return colliderComp == collider;
    });
}

void dae::PhysicsSystem::PhysicsUpdate()
{
    // Sweep pairwise to determine collisions this frame
    std::unordered_set<std::pair<const ColliderComponent*, const ColliderComponent*>, PairHash> currentCollisions{};
    currentCollisions.reserve(m_colliders.size() * 2);

    const size_t n = m_colliders.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {

            if (i == j) continue;

            auto a = m_colliders[i];
            auto b = m_colliders[j];
            const auto &[intersects, normal]{CollidersIntersecting(*a, *b)};

            if (intersects) {
                std::pair<const ColliderComponent*, const ColliderComponent*> key{a, b};
                currentCollisions.insert(key);

                // Determine previous state
                bool wasColliding = m_PreviousCollisions.contains(key);

                if (!wasColliding) {
                    // Enter
                    a->OnCollisionEnter(b, normal);
                    b->OnCollisionEnter(a, normal);
                } else {
                    // Stay
                    a->OnCollisionStay(b, normal);
                    b->OnCollisionStay(a, normal);
                }
            }
        }
    }

    // Exits: any pair that was in previous but not in current
    for (const auto& prev : m_PreviousCollisions) {
        if (!currentCollisions.contains(prev)) {
            prev.first->OnCollisionExit(prev.second);
            prev.second->OnCollisionExit(prev.first);
        }
    }

    m_PreviousCollisions.swap(currentCollisions);
}

dae::PhysicsSystem::ColliderResult dae::PhysicsSystem::CollidersIntersecting(
    ColliderComponent const &lhs,
    ColliderComponent const &rhs)
{
    const auto r1{lhs.GetColliderPosition()};
    const auto r2{rhs.GetColliderPosition()};

    // If one rectangle is on left side of the other
    if (r1.x + r1.z < r2.x || r2.x + r2.z < r1.x)
    {
        return {false, {}};
    }

    // If one rectangle is under the other
    if (r1.y > r2.y + r2.w || r2.y > r1.y + r1.w)
    {
        return {false, {}};
    }

    return {true, lhs.GetColliderCenter() - rhs.GetColliderCenter()};
}
