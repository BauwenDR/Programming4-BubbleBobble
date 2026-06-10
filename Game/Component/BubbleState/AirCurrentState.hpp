#ifndef MINIGIN_CURRENTSTATE_HPP
#define MINIGIN_CURRENTSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class AirCurrentState final : public BubbleState
    {
    public:
        BubbleStates Update() override;
        void OnCollision(uint32_t event, const dae::ColliderData &data) override;

        explicit AirCurrentState(BubbleComponent &owner);
        ~AirCurrentState() override = default;

    private:
        static constexpr float CURRENT_SPEED{128.0f};
    };
}

#endif //MINIGIN_CURRENTSTATE_HPP
