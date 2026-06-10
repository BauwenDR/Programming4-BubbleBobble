#ifndef MINIGIN_PLAYERSOUNDPRODUCER_HPP
#define MINIGIN_PLAYERSOUNDPRODUCER_HPP
#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"


class PlayerSoundProducer : public dae::GameComponent, public dae::IObserver
{
public:
    void Start() override;
    void Update() override {}

    void Notify(uint32_t event, const dae::ObserverData *data) override;

    explicit PlayerSoundProducer(dae::GameObject &owner) : GameComponent(owner) {}
};


#endif //MINIGIN_PLAYERSOUNDPRODUCER_HPP
