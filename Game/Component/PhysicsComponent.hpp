#ifndef MINIGIN_GRAVITYCOMPONENT_HPP
#define MINIGIN_GRAVITYCOMPONENT_HPP

#include <unordered_set>

#include "Component/ColliderComponent.hpp"
#include "Component/GameComponent.hpp"

#include "Event/IObserver.hpp"

namespace game
{
    class PhysicsComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void LateUpdate() override;

        void MoveHorizontal(float amount);
        void AirJump();
        void Jump();
        void SmallJump();

        void MultiplyHorizontalSpeed(float factor);

        [[nodiscard]] float GetXInput() const;
        [[nodiscard]] float GetVelX() const;
        [[nodiscard]] float GetVelY() const;
        [[nodiscard]] bool GetIsOnGround() const;
        [[nodiscard]] bool GetWasMovingLeft() const;

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        explicit PhysicsComponent(dae::GameObject &owner, bool isFacingLeft, float horizontalSpeed = 256.0f, float jumpForce = 288.0f)
            : GameComponent(owner)
              , m_maxHorizontalSpeed(horizontalSpeed)
              , m_groundAcceleration(horizontalSpeed * 8.0f)
              , m_airAcceleration(horizontalSpeed / 2.0f)
              , m_jumpForce(jumpForce)
              , m_wasMovingLeft(isFacingLeft)
        {}
        ~PhysicsComponent() override = default;
    private:
        constexpr static float GRAVITY_FORCE{60.0f * 4};
        constexpr static float TERMINAL_VELOCITY{50.0f * 4};
        constexpr static float SMALL_JUMP_DEVISOR{1.5f};
        constexpr static float MAX_JUMP_THROUGH_HEIGHT{8.0f * 4.0f};

        constexpr static float DRAG_GROUND{12.0f};
        constexpr static float DRAG_AIR{1.5f};
        constexpr static float DRAG_AIR_FALLING{2.5f};
        constexpr static float WALKING_OFF_DEVISOR{3.6f};

        dae::ColliderComponent *m_collider{};
        dae::ColliderComponent const *m_standingOn{};
        std::unordered_set<dae::ColliderComponent const *> m_ignoredColliders{};
        std::unordered_set<dae::ColliderComponent const *> m_onBubbleColliders{};

        dae::Transform m_initialPosition{};

        float m_maxHorizontalSpeed{};
        float m_groundAcceleration{};
        float m_airAcceleration{};
        float m_jumpForce{};

        float m_horizontalInput{};

        float m_velY{};
        float m_velX{};

        int32_t m_collidingWithCount{0};

        bool m_isOnGround{};
        bool m_wasMovingLeft{};
    };
}

#endif //MINIGIN_GRAVITYCOMPONENT_HPP
