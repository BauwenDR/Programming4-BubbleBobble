#ifndef MINIGIN_CURRENTSTATE_HPP
#define MINIGIN_CURRENTSTATE_HPP
#include "BubbleState.hpp"

namespace game::bubble
{
    class AirCurrentState final : public BubbleState
    {
    public:
        void Update() override;
        bool CanTrapEnemy() override;

        explicit AirCurrentState(BubbleComponent &owner);
        ~AirCurrentState() override = default;

    private:
        static constexpr float CURRENT_SPEED{128.0f};
    };
}

#endif //MINIGIN_CURRENTSTATE_HPP
