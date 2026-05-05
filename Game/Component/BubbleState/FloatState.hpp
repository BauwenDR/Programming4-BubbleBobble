#ifndef MINIGIN_BUBBLEFLOATSTATE_HPP
#define MINIGIN_BUBBLEFLOATSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class FloatState final : public BubbleState
    {
    public:
        void Update() override;
        bool CanTrapEnemy() override;

        explicit FloatState(BubbleComponent &owner);
        ~FloatState() override = default;

    private:
        constexpr static float FLOAT_SPEED{64.0f};
    };
}

#endif //MINIGIN_BUBBLEFLOATSTATE_HPP
