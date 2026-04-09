#ifndef MINIGIN_WRAPAROUNDSCREENCOMPONENT_HPP
#define MINIGIN_WRAPAROUNDSCREENCOMPONENT_HPP
#include "Component/GameComponent.hpp"

namespace game
{
    class WrapAroundScreenComponent final : public dae::GameComponent
    {
    public:

        void Start() override {}
        void Update() override;
        void Render() const override {}

        explicit WrapAroundScreenComponent(dae::GameObject &owner)
            : GameComponent(owner)
        {}

        ~WrapAroundScreenComponent() override = default;
    };
}


#endif //MINIGIN_WRAPAROUNDSCREENCOMPONENT_HPP