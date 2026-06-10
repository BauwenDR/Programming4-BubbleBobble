#ifndef MINIGIN_BUBBLESHOTSTATE_HPP
#define MINIGIN_BUBBLESHOTSTATE_HPP
#include "BubbleState.hpp"

namespace game
{
    class BubbleComponent;
}

namespace game::bubble
{
    class ShotState final : public BubbleState
    {
    public:
        BubbleStates Update() override;
        void OnCollision(uint32_t event, dae::ColliderData const &data) override;
        bool CanPop() override { return false; }

        ShotState(BubbleComponent &owner, bool movingLeft);
        ~ShotState() override = default;

    private:
        static constexpr float HORIZONTAL_SPEED{512.0f};

        float m_timeRemaining{0.7f};
        bool m_isInWall{};
        bool m_movingLeft{};
    };
}


#endif //MINIGIN_BUBBLESHOTSTATE_HPP
