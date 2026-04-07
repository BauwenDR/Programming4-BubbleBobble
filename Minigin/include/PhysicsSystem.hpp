#ifndef MINIGIN_PHYSICSSYSTEM_HPP
#define MINIGIN_PHYSICSSYSTEM_HPP
#include <unordered_set>
#include <vector>

#include "Singleton.hpp"

namespace dae {
    class ColliderComponent;

    class PhysicsSystem final : public Singleton<PhysicsSystem> {
    public:
        void RegisterCollider(ColliderComponent* collider);
        void UnregisterCollider(ColliderComponent* collider);

        void PhysicsUpdate();
    private:
        friend class Singleton;

        std::vector<ColliderComponent*> m_colliders;

        // For tracking collisions across frames: set of pairs (a,b) where a < b by pointer
        // This lets us detect enter/stay/exit
        struct PairHash {
            size_t operator()(const std::pair<const ColliderComponent*, const ColliderComponent*>& p) const noexcept {
                return std::hash<const void*>()(p.first) ^ (std::hash<const void*>()(p.second) << 1);
            }
        };
        std::unordered_set<std::pair<const ColliderComponent*, const ColliderComponent*>, PairHash> m_PreviousCollisions;
    };
}

#endif //MINIGIN_PHYSICSSYSTEM_HPP