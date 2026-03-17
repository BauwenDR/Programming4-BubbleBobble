#ifndef MINIGIN_LIVESCOMPONENT_HPP
#define MINIGIN_LIVESCOMPONENT_HPP

#include "EventManager.hpp"
#include "GameComponent.hpp"

namespace game
{
    class LivesScoreComponent final : public dae::GameComponent, public dae::IEventHandler
    {
    public:
        void Start() override {}

        void Update() override {}

        void Render() const override {}

        void DecreaseLives();
        [[nodiscard]] int GetLives() const;

        void IncreaseScore(int amount);
        [[nodiscard]] int GetScore() const;

        void HandleEvent(uint32_t event) override;

        LivesScoreComponent(dae::GameObject &owner, int playerNumber);
        ~LivesScoreComponent() override;

        LivesScoreComponent(const LivesScoreComponent &other) = delete;
        LivesScoreComponent(LivesScoreComponent &&other) noexcept = delete;
        LivesScoreComponent & operator=(const LivesScoreComponent &other) = delete;
        LivesScoreComponent & operator=(LivesScoreComponent &&other) noexcept = delete;

    private:
        static constexpr int SMALL_SCORE_AMOUNT{10};
        static constexpr int BIG_SCORE_AMOUNT{100};

        uint32_t m_smallScoreEventId{};
        uint32_t m_bigScoreEventId{};

        int m_lives{3};
        int m_score{0};
    };
}

#endif //MINIGIN_LIVESCOMPONENT_HPP