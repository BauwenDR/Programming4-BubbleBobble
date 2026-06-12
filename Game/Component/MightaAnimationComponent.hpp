#ifndef MINIGIN_MIGHTAANIMATIONCOMPONENT_HPP
#define MINIGIN_MIGHTAANIMATIONCOMPONENT_HPP
#include "Component/GameComponent.hpp"

namespace game {
    class AnimationComponent;
    class PhysicsComponent;

    class MightaAnimationComponent : public dae::GameComponent {
    public:
        void Start() override;
        void Update() override;

        explicit MightaAnimationComponent(dae::GameObject &owner);
        ~MightaAnimationComponent() override = default;

    private:
        PhysicsComponent *m_physicsComponent{nullptr};
        AnimationComponent *m_animationComponent{nullptr};
    };
}

#endif //MINIGIN_MIGHTAANIMATIONCOMPONENT_HPP
