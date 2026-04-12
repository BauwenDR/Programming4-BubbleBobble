#include "AnimationComponent.hpp"

#include <cmath>

#include "GameObject.hpp"
#include "Time.hpp"
#include "Component/TextureComponent.hpp"

void game::AnimationComponent::Start()
{
    m_spriteTexture = GetGameObject().GetComponent<dae::TextureComponent>();

    UpdateTexture();
}

void game::AnimationComponent::LateUpdate()
{
    m_frameElapsedTime += Time::timeDelta();

    if (m_frameElapsedTime > m_frameTime)
    {
        m_frameElapsedTime = std::fmod(m_frameElapsedTime, m_frameTime);

        ++m_currentFrame;
        m_currentFrame %= m_currentAnimation->frames;

        UpdateTexture();
    }
}

void game::AnimationComponent::RequestAnimationState(AnimationData const *newState)
{
    if (newState == m_currentAnimation || newState != m_requestedAnimation)
    {
        m_animationCooldown = 0;
        m_requestedAnimation = newState;
        return;
    }

    m_animationCooldown++;
    if (m_animationCooldown >= ANIMATION_COOLDOWN_FRAMES)
    {
        m_animationCooldown = 0;
        SetAnimationState(newState);
    }
}

void game::AnimationComponent::SetAnimationState(AnimationData const *newState)
{
    m_currentAnimation = newState;
    m_currentFrame = 0;

    UpdateTexture();
}

game::AnimationComponent::AnimationComponent(
    dae::GameObject &owner,
    AnimationData const *initialAnimation,
    float frameTime,
    glm::vec2 const &offset
)
    : GameComponent(owner)
      , m_spriteOffset(offset)
      , m_currentAnimation(initialAnimation)
      , m_frameTime(frameTime)
{
}

void game::AnimationComponent::UpdateTexture() const
{
    m_spriteTexture->SetSpriteOffset(glm::vec2{
        m_currentAnimation->col + m_spriteOffset.x + static_cast<float>(m_currentFrame),
        m_currentAnimation->row + m_spriteOffset.y
    });
}
