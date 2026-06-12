#ifndef MINIGIN_LIVESCOMPONENT_HPP
#define MINIGIN_LIVESCOMPONENT_HPP

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class PhysicsComponent;

    class LiveChangedData : public dae::ObserverData
    {
    public:
        bool isOneUp{};
        int32_t newLives{};

        LiveChangedData(bool isOneUp, int32_t newLives)
            : isOneUp(isOneUp),
              newLives(newLives)
        {
        }

        ~LiveChangedData() override = default;
    };

    class LivesScoreComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        [[nodiscard]] int32_t GetLives() const;
        [[nodiscard]] int32_t GetScore() const;

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        explicit LivesScoreComponent(dae::GameObject &owner);

    private:
        constexpr static float INVULNERABILITY_TIME{3.0f};

        int32_t m_lives{3};
        int32_t m_score{0};

        float m_invulnerabilityTimer{};

        void OnScoreChange(dae::ObserverData const *data);
        void OnEnemyCollision(dae::ObserverData const *data);
    };
}

#endif //MINIGIN_LIVESCOMPONENT_HPP