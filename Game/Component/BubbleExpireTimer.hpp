#ifndef MINIGIN_BUBBLEEXPIRETIMER_HPP
#define MINIGIN_BUBBLEEXPIRETIMER_HPP
#include "Component/GameComponent.hpp"

namespace dae
{
    class TextureComponent;
}

namespace game
{
    class BubbleComponent;

    class BubbleExpireTimer final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;

        BubbleExpireTimer(dae::GameObject &owner, float timeToLive);
    private:
        constexpr static float WARNING_TIME_PERCENT{0.5f};
        constexpr static float DANGER_TIME_PERCENT{0.75f};

        constexpr static float WARNING_OFFSET{2.0f};
        constexpr static float DANGER_OFFSET{3.0f};

        BubbleComponent *m_bubble{};
        dae::TextureComponent *m_texture{};

        const float m_timeToLive{};
        float m_timeLived{};
        float m_currentOffset{};

    };
}

#endif //MINIGIN_BUBBLEEXPIRETIMER_HPP
