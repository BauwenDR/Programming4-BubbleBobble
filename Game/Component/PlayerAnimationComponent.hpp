#ifndef MINIGIN_PLAYERANIMATIONCOMPONENT_HPP
#define MINIGIN_PLAYERANIMATIONCOMPONENT_HPP

#include "Component/GameComponent.hpp"

namespace dae
{
    class PhysicsComponent;
    class TextureComponent;
}

namespace game
{
    class AnimationComponent;

    class PlayerAnimationComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        explicit PlayerAnimationComponent(dae::GameObject &owner, bool facingLeft)
            : GameComponent(owner)
              , m_wasMovingLeft(facingLeft)
        {
        }
        ~PlayerAnimationComponent() override = default;

    private:
        dae::PhysicsComponent *m_physicsComponent{};
        AnimationComponent *m_animationComponent{};

        bool m_wasMovingLeft{};
    };
}

#endif //MINIGIN_PLAYERANIMATIONCOMPONENT_HPP
