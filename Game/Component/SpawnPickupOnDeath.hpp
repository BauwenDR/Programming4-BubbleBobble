#ifndef MINIGIN_SPAWNPICKUPONDEATH_HPP
#define MINIGIN_SPAWNPICKUPONDEATH_HPP
#include <cstdint>

#include "Component/GameComponent.hpp"


class SpawnPickupOnDeath final : public dae::GameComponent
{
public:
    int32_t PopMultiplier{1};

    void Update() override {}

    void OnDelete() override;

    SpawnPickupOnDeath(dae::GameObject &owner, int32_t worth);

private:
    int32_t m_worth{};
};

#endif //MINIGIN_SPAWNPICKUPONDEATH_HPP
