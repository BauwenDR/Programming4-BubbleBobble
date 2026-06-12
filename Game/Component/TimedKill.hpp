#ifndef MINIGIN_TIMEDKILL_HPP
#define MINIGIN_TIMEDKILL_HPP
#include "Component/GameComponent.hpp"

namespace dae
{
    class TextureComponent;
}

namespace game
{
    class TimedKill final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;

        TimedKill(dae::GameObject &owner, float timeToLive);

    private:
        constexpr static float FLICKER_START_PERCENT{0.75f};

        float const m_timeToLive{};
        float m_timeLived{};
    };
}

#endif //MINIGIN_TIMEDKILL_HPP
