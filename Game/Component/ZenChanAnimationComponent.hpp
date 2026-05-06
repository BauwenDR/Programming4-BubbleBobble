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

        explicit ZenChanAnimationComponent(dae::GameObject &owner);
        ~ZenChanAnimationComponent() override = default;

    private:
        PhysicsComponent *m_physicsComponent{nullptr};
        AnimationComponent *m_animationComponent{nullptr};
    };
}

#endif //MINIGIN_ZENCHANANIMATIONCOMPONENT_HPP