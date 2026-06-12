#ifndef MINIGIN_BOULDERCOMPONENT_HPP
#define MINIGIN_BOULDERCOMPONENT_HPP
#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class BoulderComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;

        void Notify(uint32_t event, dae::ObserverData const* data) override;

        BoulderComponent(dae::GameObject &owner, bool moveLeft);

    private:
        constexpr static float BOULDER_SPEED{255.0f};
        bool m_isMovingLeft{};
    };
}

#endif //MINIGIN_BOULDERCOMPONENT_HPP
