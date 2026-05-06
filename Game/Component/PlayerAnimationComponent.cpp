#include "PlayerAnimationComponent.hpp"

#include "Component/AnimationComponent.hpp"
#include "Animations/PlayerAnimations.hpp"

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"

void game::PlayerAnimationComponent::Start()
{
    m_animationComponent = GetGameObject().GetComponent<AnimationComponent>();
    m_physicsComponent = GetGameObject().GetComponent<PhysicsComponent>();
}

void game::PlayerAnimationComponent::Update()
{
    if (!m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelY() > 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_physicsComponent->GetWasMovingLeft()
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationStates::FallingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationStates::FallingRight))
            );
        } else if (m_physicsComponent->GetVelY() < 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_physicsComponent->GetWasMovingLeft()
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationStates::JumpingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationStates::JumpingRight))
            );
        }
    }

    if (m_physicsComponent->GetIsOnGround())
    {
        if (m_physicsComponent->GetVelX() < -1.0f || m_physicsComponent->GetVelX() > 1.0f)
        {
            m_animationComponent->RequestAnimationState(&
                (m_physicsComponent->GetWasMovingLeft()
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationStates::WalkingLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationStates::WalkingRight))
            );
        } else
        {
            m_animationComponent->RequestAnimationState(&
                (m_physicsComponent->GetWasMovingLeft()
                     ? PLAYER_ANIMATIONS.at(PlayerAnimationStates::IdleLeft)
                     : PLAYER_ANIMATIONS.at(PlayerAnimationStates::IdleRight))
            );
        }
    }
}

game::PlayerAnimationComponent::PlayerAnimationComponent(dae::GameObject &owner)
: GameComponent(owner)
{
}
