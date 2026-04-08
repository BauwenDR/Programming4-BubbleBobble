#ifndef MINIGIN_LIVESCOMPONENT_HPP
#define MINIGIN_LIVESCOMPONENT_HPP

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class LivesScoreComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void Render() const override {}

        [[nodiscard]] int GetLives() const;
        [[nodiscard]] int GetScore() const;

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        explicit LivesScoreComponent(dae::GameObject &owner);

    private:
        int m_lives{3};
        int m_score{0};
    };
}

#endif //MINIGIN_LIVESCOMPONENT_HPP