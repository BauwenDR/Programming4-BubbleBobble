#ifndef MINIGIN_ANIMATIONCOMPONENT_HPP
#define MINIGIN_ANIMATIONCOMPONENT_HPP
#include <glm/vec2.hpp>

#include "Animations/AnimationData.hpp"
#include "Component/GameComponent.hpp"

namespace dae
{
    class TextureComponent;
}

namespace game
{
    class AnimationComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void LateUpdate() override;

        void RequestAnimationState(AnimationData const *newState);
        void SetAnimationState(AnimationData const *newState);

        AnimationComponent(
            dae::GameObject &owner,
            AnimationData const *initialAnimation,
            glm::vec2 const &offset = {0.0f, 0.0f}
        );
        ~AnimationComponent() override = default;
    private:
        constexpr static int ANIMATION_COOLDOWN_FRAMES{2};
        constexpr static float FRAME_TIME{1.0f/2.0f};

        glm::vec2 m_spriteOffset{};

        dae::TextureComponent *m_spriteTexture{};

        AnimationData const *m_currentAnimation{nullptr};
        AnimationData const *m_requestedAnimation{nullptr};

        float m_frameElapsedTime{};

        int m_currentFrame{};
        int m_animationCooldown{};

        void UpdateTexture() const;
    };
}


#endif //MINIGIN_ANIMATIONCOMPONENT_HPP