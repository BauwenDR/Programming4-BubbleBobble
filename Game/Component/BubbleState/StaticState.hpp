#ifndef MINIGIN_STATICSTATE_HPP
#define MINIGIN_STATICSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class StaticState final : public BubbleState
    {
    public:
        void Update() override;
        bool CanTrapEnemy() override;

        explicit StaticState(BubbleComponent &owner);
        ~StaticState() override = default;
    };
}

#endif //MINIGIN_STATICSTATE_HPP
