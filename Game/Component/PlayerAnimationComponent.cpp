#include "PlayerAnimationComponent.hpp"

#include "Component/AnimationComponent.hpp"
#include "Animations/PlayerAnimations.hpp"

#include "Component/PhysicsComponent.hpp"
#include "GameObject.hpp"

void game::PlayerAnimationComponent::Start()
{
    m_animationComponent = GetGameObject().GetComponent<AnimationComponent>();
    m_physicsComponent = GetGameObject().GetComponent<dae::PhysicsComponent>();
}

void game::PlayerAnimationComponent::Update()
{
    if (m_physicsComponent->GetXInput() != 0.0f)
    {
        m_wasMovingLeft = m_physicsComponent->GetXInput() < 0.0f;
    }

    if (!m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelY() > 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_wasMovingLeft
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationState::FallingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationState::FallingRight))
            );
        } else if (m_physicsComponent->GetVelY() < 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_wasMovingLeft
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationState::JumpingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationState::JumpingRight))
            );
        }
    }

    if (m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelX() < -1.0f || m_physicsComponent->GetVelX() > 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_wasMovingLeft
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationState::WalkingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationState::WalkingRight))
            );
        } else
        {
            m_animationComponent->RequestAnimationState(&
                (m_wasMovingLeft
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationState::IdleLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationState::IdleRight))
            );
        }
    }
}
