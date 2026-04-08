#ifndef MINIGIN_GRAVITYCOMPONENT_HPP
#define MINIGIN_GRAVITYCOMPONENT_HPP

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

        void Notify(const GameObject &object, uint32_t event, const ObserverData *data) override;

        explicit PhysicsComponent(GameObject &owner) : GameComponent(owner) {}
        ~PhysicsComponent() override = default;
    private:
        constexpr static float GRAVITY_FORCE{60.0f * 4};
        constexpr static float TERMINAL_VELOCITY{50.0f * 4};
        constexpr static float JUMP_FORCE{72.0f * 4};
        constexpr static float MAX_JUMP_THROUGH_HEIGHT{8.0f * 4.0f};

        ColliderComponent *m_collider{};
        ColliderComponent const *m_standingOn{};
        std::unordered_map<ColliderComponent const *, bool> *m_collidingWith{new std::unordered_map<ColliderComponent const *, bool>()};

        float m_velY{};
        float m_velX{};

        float m_maxSpeedGround{300.0f};   // tweak: max speed on ground (units/sec)
        float m_maxSpeedAir{160.0f};      // tweak: max speed in air
        float m_accelGround{1500.0f};     // acceleration when on ground
        float m_accelAir{600.0f};         // acceleration when in air
        float m_dragGround{12.0f};        // ground braking / friction
        float m_dragAir{2.0f};

        bool m_isOnGround{};
    };
}

#endif //MINIGIN_GRAVITYCOMPONENT_HPP
