#ifndef MINIGIN_PLAYERANIMATIONCOMPONENT_HPP
#define MINIGIN_PLAYERANIMATIONCOMPONENT_HPP

#include "Component/GameComponent.hpp"

namespace dae
{
    class TextureComponent;
}

namespace game
{
    class AnimationComponent;
    class PhysicsComponent;

    class PlayerAnimationComponent final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;

        explicit PlayerAnimationComponent(dae::GameObject &owner);
        ~PlayerAnimationComponent() override = default;

    private:
        PhysicsComponent *m_physicsComponent{};
        AnimationComponent *m_animationComponent{};
    };
}

#endif //MINIGIN_PLAYERANIMATIONCOMPONENT_HPP
