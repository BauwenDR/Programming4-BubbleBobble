#include "ZenChanAnimationComponent.hpp"

#include "Component/AnimationComponent.hpp"

#include "Component/PhysicsComponent.hpp"
#include "GameObject.hpp"
#include "Animations/ZenChanAnimation.hpp"

void game::ZenChanAnimationComponent::Start()
{
    m_animationComponent = GetGameObject().GetComponent<AnimationComponent>();
    m_physicsComponent = GetGameObject().GetComponent<dae::PhysicsComponent>();
}

void game::ZenChanAnimationComponent::Update()
{
    if (m_physicsComponent->GetXInput() != 0.0f)
    {
        m_wasMovingLeft = m_physicsComponent->GetXInput() < 0.0f;
    }

    m_animationComponent->RequestAnimationState(&
        (m_wasMovingLeft
             ? ZENCHAN_ANIMATIONS.at(ZenChanAnimationState::WalkingLeft)
             : ZENCHAN_ANIMATIONS.at(ZenChanAnimationState::WalkingRight))
    );
}
