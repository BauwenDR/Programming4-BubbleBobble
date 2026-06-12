#ifndef MINIGIN_SPAWNPICKUPONDEATH_HPP
#define MINIGIN_SPAWNPICKUPONDEATH_HPP
#include <cstdint>

#include "Component/GameComponent.hpp"
#include "Event/EventManager.hpp"

namespace game
{
    class SpawnPickupOnDeath final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        int32_t PopMultiplier{1};

        void Start() override;
        void Update() override {}
        void OnDelete() override;

        void HandleEvent(uint32_t event) override;

        SpawnPickupOnDeath(dae::GameObject &owner, int32_t worth);

    private:
        int32_t m_worth{};
        bool m_dropEnabled{};
    };
}

#endif //MINIGIN_SPAWNPICKUPONDEATH_HPP
