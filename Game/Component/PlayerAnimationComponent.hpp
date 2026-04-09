#ifndef MINIGIN_PLAYERANIMATIONCOMPONENT_HPP
#define MINIGIN_PLAYERANIMATIONCOMPONENT_HPP

#include "PlayerAnimations.hpp"

#include "Component/GameComponent.hpp"

namespace dae
{
    class PhysicsComponent;
    class TextureComponent;
}

namespace game
{
    class PlayerAnimationComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        explicit PlayerAnimationComponent(dae::GameObject &owner, int playerNumber);
        ~PlayerAnimationComponent() override = default;

    private:
        constexpr static int ANIMATION_COOLDOWN_FRAMES{2};
        constexpr static float FRAME_TIME{1.0f/2.0f};

        dae::TextureComponent *m_spriteTexture{};
        dae::PhysicsComponent *m_physicsComponent{};

        AnimationData const *m_currentAnimationData{};
        PlayerAnimationState m_currentAnimation{};
        PlayerAnimationState m_requestedAnimation{};

        const float m_playerOffset{};

        float m_frameElapsedTime{};

        int m_currentFrame{};
        int m_animationCooldown{};

        bool m_wasMovingLeft{};

        void CalculateNextAnimationState();
        void RequestAnimationState(PlayerAnimationState newState);
        void SetAnimationState(PlayerAnimationState newState);
        void UpdateAnimationFrame();
        void UpdateTexture() const;
    };
}

#endif //MINIGIN_PLAYERANIMATIONCOMPONENT_HPP