#ifndef MINIGIN_STATICSTATE_HPP
#define MINIGIN_STATICSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class StaticState final : public BubbleState
    {
    public:
        BubbleStates Update() override;
        void OnCollision(uint32_t event, dae::ColliderData const &data) override;

        explicit StaticState(BubbleComponent &owner);
        ~StaticState() override = default;
    };
}

#endif //MINIGIN_STATICSTATE_HPP
