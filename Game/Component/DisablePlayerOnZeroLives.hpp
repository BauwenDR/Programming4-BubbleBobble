#ifndef MINIGIN_DISABLEONZEROLIVES_HPP
#define MINIGIN_DISABLEONZEROLIVES_HPP
#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class DisablePlayerOnZeroLives final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}

        void Notify(uint32_t event, dae::ObserverData const* data) override;

        explicit DisablePlayerOnZeroLives(dae::GameObject &owner);
    private:
        void Disable() const;
    };
}

#endif //MINIGIN_DISABLEONZEROLIVES_HPP
