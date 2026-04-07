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
    std::unordered_set<std::pair<const ColliderComponent*, const ColliderComponent*>, PairHash> currentCollisions;
    currentCollisions.reserve(m_colliders.size() * 2);

    const size_t n = m_colliders.size();
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = i + 1; j < n; ++j) {
            auto a = m_colliders[i];
            auto b = m_colliders[j];

            if (a->Intersects(*b)) {
                std::pair<const ColliderComponent*, const ColliderComponent*> key{a, b};
                currentCollisions.insert(key);

                // Determine previous state
                bool wasColliding = m_PreviousCollisions.contains(key);

                if (!wasColliding) {
                    // Enter
                    a->OnCollisionEnter(b);
                    b->OnCollisionEnter(a);
                } else {
                    // Stay
                    a->OnCollisionStay(b);
                    b->OnCollisionStay(a);
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

    // Note: Gravity handling is done by GravityComponent::Update which should be called elsewhere,
    // but you can also call it here if you track gravity components inside PhysicsSystem.
}
