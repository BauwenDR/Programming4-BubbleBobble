#ifndef MINIGIN_GRAVITYCOMPONENT_HPP
#define MINIGIN_GRAVITYCOMPONENT_HPP

#include <unordered_set>

#include "ColliderComponent.hpp"
#include "GameComponent.hpp"

#include "Event/IObserver.hpp"

namespace dae
{
    class PhysicsComponent final : public GameComponent, public IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        void MoveHorizontal(float amount);
        void Jump();

        void Notify(uint32_t event, const ObserverData *data) override;

        explicit PhysicsComponent(GameObject &owner) : GameComponent(owner) {}
        ~PhysicsComponent() override = default;
    private:
        constexpr static float GRAVITY_FORCE{60.0f * 4};
        constexpr static float TERMINAL_VELOCITY{50.0f * 4};
        constexpr static float JUMP_FORCE{72.0f * 4};
        constexpr static float MAX_JUMP_THROUGH_HEIGHT{8.0f * 4.0f};

        constexpr static float MAX_HORIZONTAL_SPEED{256.0f};
        constexpr static float ACCELERATION_GROUND{512.0f * 4.0f};
        constexpr static float ACCELERATION_AIR{128.0f};
        constexpr static float DRAG_GROUND{12.0f};
        constexpr static float DRAG_AIR{1.5f};
        constexpr static float DRAG_AIR_FALLING{2.5f};
        constexpr static float WALKING_OFF_DEVISOR{3.6f};

        ColliderComponent *m_collider{};
        ColliderComponent const *m_standingOn{};
        std::unordered_set<ColliderComponent const *> m_ignoredColliders{};

        float m_maxHorizontalSpeed{MAX_HORIZONTAL_SPEED};   // The max speed can increase
        float m_velY{};
        float m_velX{};

        int m_collidingWithCount{0};

        bool m_isOnGround{};
    };
}

#endif //MINIGIN_GRAVITYCOMPONENT_HPP
