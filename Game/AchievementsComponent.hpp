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
        void Start() override {}
        void Update() override {}
        void Render() const override {}

        void Notify(dae::GameObject &object, uint32_t event) override;

        AchievementsComponent(dae::GameObject &owner, const std::vector<dae::GameObject*> &players);
        ~AchievementsComponent() override;

        AchievementsComponent(const AchievementsComponent &other) = delete;
        AchievementsComponent(AchievementsComponent &&other) noexcept = delete;
        AchievementsComponent & operator=(const AchievementsComponent &other) = delete;
        AchievementsComponent & operator=(AchievementsComponent &&other) noexcept = delete;

    private:
        std::vector<dae::GameObject*> m_players{};
    };
}


#endif //MINIGIN_ACHIEVEMENTSCOMPONENT_HPP