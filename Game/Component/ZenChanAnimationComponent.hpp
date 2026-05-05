#ifndef MINIGIN_ZENCHANANIMATIONCOMPONENT_HPP
#define MINIGIN_ZENCHANANIMATIONCOMPONENT_HPP
#include "Component/GameComponent.hpp"

namespace game
{
    class PhysicsComponent;
}

namespace game
{
    class AnimationComponent;

    class ZenChanAnimationComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;

        ZenChanAnimationComponent(dae::GameObject &owner, bool facingLeft)
            : GameComponent(owner)
              , m_wasMovingLeft(facingLeft) {}
        ~ZenChanAnimationComponent() override = default;

    private:
        PhysicsComponent *m_physicsComponent{nullptr};
        AnimationComponent *m_animationComponent{nullptr};

        bool m_wasMovingLeft{false};
    };
}

#endif //MINIGIN_ZENCHANANIMATIONCOMPONENT_HPP