#ifndef MINIGIN_ACHIEVEMENTSCOMPONENT_HPP
#define MINIGIN_ACHIEVEMENTSCOMPONENT_HPP

#include <cstdint>

#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace game
{
    // This component should just be attached to an empty game object somewhere in the scene
    // If the steamworks SDK cannot be found this component will not do anything
    class AchievementsComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override;

        void Notify(dae::GameObject &object, uint32_t event) override;

        explicit AchievementsComponent(dae::GameObject &owner);
        ~AchievementsComponent() override;

        AchievementsComponent(const AchievementsComponent &other) = delete;
        AchievementsComponent(AchievementsComponent &&other) noexcept = delete;
        AchievementsComponent & operator=(const AchievementsComponent &other) = delete;
        AchievementsComponent & operator=(AchievementsComponent &&other) noexcept = delete;
    };
}


#endif //MINIGIN_ACHIEVEMENTSCOMPONENT_HPP