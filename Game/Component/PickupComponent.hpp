#ifndef MINIGIN_PICKUPCOMPONENT_HPP
#define MINIGIN_PICKUPCOMPONENT_HPP

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class PickupData final : public dae::ObserverData
    {
    public:
        int worth;

        explicit PickupData(int worth) : worth(worth) {}
        ~PickupData() override = default;
    };

    class PickupComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void Render() const override {}

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        PickupComponent(dae::GameObject &owner, int worth);
        ~PickupComponent() override;

        PickupComponent(const PickupComponent &other) = delete;
        PickupComponent(PickupComponent &&other) noexcept = delete;
        PickupComponent &operator=(const PickupComponent &other) = delete;
        PickupComponent &operator=(PickupComponent &&other) noexcept = delete;

    private:
        int m_worth{};
    };
}


#endif //MINIGIN_PICKUPCOMPONENT_HPP