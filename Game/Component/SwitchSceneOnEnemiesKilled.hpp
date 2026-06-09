#ifndef MINIGIN_STAGEMANAGER_HPP
#define MINIGIN_STAGEMANAGER_HPP
#include <cstdint>

#include "Component/GameComponent.hpp"
#include "Event/EventManager.hpp"

namespace game
{
    class SwitchSceneOnEnemiesKilled final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        void Start() override;
        void Update() override;

        void HandleEvent(uint32_t event) override;

        SwitchSceneOnEnemiesKilled(dae::GameObject &owner, int threshold);
        ~SwitchSceneOnEnemiesKilled() override;

        SwitchSceneOnEnemiesKilled(SwitchSceneOnEnemiesKilled const &other) = delete;
        SwitchSceneOnEnemiesKilled &operator=(SwitchSceneOnEnemiesKilled const &other) = delete;
        SwitchSceneOnEnemiesKilled(SwitchSceneOnEnemiesKilled &&other) noexcept = delete;
        SwitchSceneOnEnemiesKilled &operator=(SwitchSceneOnEnemiesKilled &&other) noexcept = delete;

    private:
        constexpr static float SWITCH_DELAY{3.0f};

        float m_switchCountdown{};
        int32_t const m_enemyThreshold{};
        int32_t m_remainingEnemies{};
        bool m_canSwitch{};
    };
}
#endif //MINIGIN_STAGEMANAGER_HPP
