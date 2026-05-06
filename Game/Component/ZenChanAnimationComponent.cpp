#include "ZenChanAnimationComponent.hpp"

#include <iostream>

#include "Component/AnimationComponent.hpp"

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"
#include "Animations/ZenChanAnimation.hpp"

void game::ZenChanAnimationComponent::Start()
{
    m_animationComponent = GetGameObject().GetComponent<AnimationComponent>();
    m_physicsComponent = GetGameObject().GetComponent<PhysicsComponent>();
}

void game::ZenChanAnimationComponent::Update()
{
    m_animationComponent->RequestAnimationState(&
        (m_physicsComponent->GetWasMovingLeft()
             ? ZEN_CHAN_ANIMATIONS.at(ZenChanAnimationStates::WalkingLeft)
             : ZEN_CHAN_ANIMATIONS.at(ZenChanAnimationStates::WalkingRight))
    );
}

game::ZenChanAnimationComponent::ZenChanAnimationComponent(dae::GameObject &owner)
    : GameComponent(owner)
{
}
