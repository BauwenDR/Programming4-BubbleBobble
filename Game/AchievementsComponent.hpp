#ifndef MINIGIN_ACHIEVEMENTSCOMPONENT_HPP
#define MINIGIN_ACHIEVEMENTSCOMPONENT_HPP
#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace game
{
    // This component should just be attached to an empty game object somewhere in the scene
    class AchievementsComponent : public dae::GameComponent, public dae::IObserver
    {
    };
}

#endif //MINIGIN_ACHIEVEMENTSCOMPONENT_HPP