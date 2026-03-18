#ifndef MINIGIN_LIVESCOMPONENT_HPP
#define MINIGIN_LIVESCOMPONENT_HPP

#include "GameComponent.hpp"

namespace game
{
    class LivesScoreComponent final : public dae::GameComponent
    {
    public:
        void Start() override {}

        void Update() override {}

        void Render() const override {}

        void DecreaseLives();
        [[nodiscard]] int GetLives() const;

        void IncreaseScore(int amount);
        [[nodiscard]] int GetScore() const;

        LivesScoreComponent(dae::GameObject &owner);

    private:

        int m_lives{3};
        int m_score{0};
    };
}

#endif //MINIGIN_LIVESCOMPONENT_HPP