#include "PhysicsSystem.hpp"

#include <algorithm>

#include <glm/glm.hpp>

#include "Component/ColliderComponent.hpp"

void dae::PhysicsSystem::RegisterCollider(ColliderComponent *collider)
{
    m_colliders.push_back(collider);
}

void dae::PhysicsSystem::UnregisterCollider(ColliderComponent *collider)
{
    std::erase_if(m_colliders, [collider](ColliderComponent const * colliderComp)
    {
        return colliderComp == collider;
    });
}

void dae::PhysicsSystem::PhysicsUpdate()
{
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

                bool wasColliding = m_PreviousCollisions.contains(key);

                if (!wasColliding) {
                    a->OnCollisionEnter(b, normal);
                    b->OnCollisionEnter(a, normal);
                } else {
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
    const auto r1{lhs.GetColliderPosition()}; // x,y = top-left; z = width; w = height
    const auto r2{rhs.GetColliderPosition()};

    if (r1.x + r1.z < r2.x || r2.x + r2.z < r1.x)
    {
        return {false, {}};
    }

    if (r1.y > r2.y + r2.w || r2.y > r1.y + r1.w)
    {
        return {false, {}};
    }

    const glm::vec2 c1{ r1.x + r1.z * 0.5f, r1.y + r1.w * 0.5f };
    const glm::vec2 c2{ r2.x + r2.z * 0.5f, r2.y + r2.w * 0.5f };

    // Calculate what axis we overlap with the most, point the normal towards that axis
    const glm::vec2 distance = c1 - c2;
    const glm::vec2 extents{ r1.z * 0.5f + r2.z * 0.5f, r1.w * 0.5f + r2.w * 0.5f };
    const glm::vec2 penetration = extents - glm::abs(distance);

    if (penetration.x < penetration.y)
    {
        const float sx = distance.x < 0.0f ? -1.0f : 1.0f;
        return { true, glm::vec2(sx, 0.0f) };
    }

    const float sy = distance.y < 0.0f ? -1.0f : 1.0f;
    return { true, glm::vec2(0.0f, sy) };
}
