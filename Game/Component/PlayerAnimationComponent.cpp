#include "PlayerAnimationComponent.hpp"

#include "Component/PhysicsComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "GameObject.hpp"
#include "Time.hpp"

void game::PlayerAnimationComponent::Start()
{
    m_spriteTexture = GetGameObject().GetComponent<dae::TextureComponent>();
    m_physicsComponent = GetGameObject().GetComponent<dae::PhysicsComponent>();

    SetAnimationState(m_currentAnimation);
}

void game::PlayerAnimationComponent::Update()
{
    CalculateNextAnimationState();
    UpdateAnimationFrame();
}

game::PlayerAnimationComponent::PlayerAnimationComponent(dae::GameObject &owner, int playerNumber)
    : GameComponent(owner)
      , m_playerOffset(static_cast<float>(playerNumber) * 4.0f)
{
}

void game::PlayerAnimationComponent::CalculateNextAnimationState()
{
    if (m_physicsComponent->GetXInput() != 0.0f)
    {
        m_wasMovingLeft = m_physicsComponent->GetXInput() < 0.0f;
    }

    if (!m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelY() > 1.0f)
        {
            RequestAnimationState(m_wasMovingLeft
                                      ? PlayerAnimationState::FallingLeft
                                      : PlayerAnimationState::FallingRight
            );
        } else if (m_physicsComponent->GetVelY() < 1.0f)
        {
            RequestAnimationState(m_wasMovingLeft
                                      ? PlayerAnimationState::JumpingLeft
                                      : PlayerAnimationState::JumpingRight
            );
        }
    }

    if (m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelX() < -1.0f || m_physicsComponent->GetVelX() > 1.0f)
        {
            RequestAnimationState(m_wasMovingLeft
                                      ? PlayerAnimationState::WalkingLeft
                                      : PlayerAnimationState::WalkingRight
            );
        } else
        {
            RequestAnimationState(m_wasMovingLeft
                                      ? PlayerAnimationState::IdleLeft
                                      : PlayerAnimationState::IdleRight
            );
        }
    }

}

void game::PlayerAnimationComponent::RequestAnimationState(PlayerAnimationState newState)
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

void game::PlayerAnimationComponent::SetAnimationState(PlayerAnimationState newState)
{
    m_currentAnimation = newState;
    m_currentAnimationData = &PLAYER_ANIMATIONS.at(newState);
    m_currentFrame = 0.0f;

    UpdateTexture();
}

void game::PlayerAnimationComponent::UpdateAnimationFrame()
{
    m_frameElapsedTime += Time::timeDelta();

    if (m_frameElapsedTime > FRAME_TIME)
    {
        m_frameElapsedTime = std::fmod(m_frameElapsedTime, FRAME_TIME);

        ++m_currentFrame;
        m_currentFrame %= m_currentAnimationData->frames;

        UpdateTexture();
    }
}

void game::PlayerAnimationComponent::UpdateTexture() const
{
    m_spriteTexture->SetSpriteOffset(glm::vec2{
        m_currentAnimationData->col + m_playerOffset + static_cast<float>(m_currentFrame),
        m_currentAnimationData->row
    });
}
