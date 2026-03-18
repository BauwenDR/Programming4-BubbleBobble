#ifndef MINIGIN_ACHIEVEMENTSCOMPONENT_HPP
#define MINIGIN_ACHIEVEMENTSCOMPONENT_HPP

#include <cstdint>
#include <vector>

#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace game
{
    class LivesScoreComponent;

    // If the steamworks SDK cannot be found this component will not do anything (not even register itself)
    class AchievementsComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void Render() const override {}

        void Notify(dae::GameObject &object, uint32_t event) override;

        AchievementsComponent(dae::GameObject &owner, dae::GameObject &player);

    private:
        dae::GameObject &m_observingPlayer;
        LivesScoreComponent *m_livesScoreComponent{};
    };
}


#endif //MINIGIN_ACHIEVEMENTSCOMPONENT_HPP