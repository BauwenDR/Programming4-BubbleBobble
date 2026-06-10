#ifndef MINIGIN_BUBBLEFLOATSTATE_HPP
#define MINIGIN_BUBBLEFLOATSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class FloatState final : public BubbleState
    {
    public:
        BubbleStates Update() override;
        void OnCollision(uint32_t event, const dae::ColliderData &data) override;

        explicit FloatState(BubbleComponent &owner);
        ~FloatState() override = default;

    private:
        constexpr static float FLOAT_SPEED{64.0f};
    };
}

#endif //MINIGIN_BUBBLEFLOATSTATE_HPP
