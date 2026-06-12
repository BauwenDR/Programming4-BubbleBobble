#include "MightaAnimationComponent.hpp"

#include "Component/AnimationComponent.hpp"

#include "PhysicsComponent.hpp"
#include "GameObject.hpp"
#include "Animations/MightaAnimation.hpp"

void game::MightaAnimationComponent::Start() {
    m_animationComponent = GetGameObject().GetComponent<AnimationComponent>();
    m_physicsComponent = GetGameObject().GetComponent<PhysicsComponent>();
}

void game::MightaAnimationComponent::Update() {
    m_animationComponent->RequestAnimationState(&
        (m_physicsComponent->GetWasMovingLeft()
             ? MIGHTA_ANIMATIONS.at(MightaAnimationStates::WalkingLeft)
             : MIGHTA_ANIMATIONS.at(MightaAnimationStates::WalkingRight))
    );
}

game::MightaAnimationComponent::MightaAnimationComponent(dae::GameObject &owner)
    : GameComponent(owner)
{
}
