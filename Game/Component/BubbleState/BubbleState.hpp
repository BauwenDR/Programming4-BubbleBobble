#ifndef MINIGIN_IBUBBLESTATE_HPP
#define MINIGIN_IBUBBLESTATE_HPP

#include "Component/BubbleComponent.hpp"
#include "Component/ColliderComponent.hpp"

namespace game
{
    class BubbleComponent;
}

namespace game::bubble
{
    class BubbleState
    {
    public:
        virtual BubbleStates Update() = 0;
        virtual void OnCollision(uint32_t event, dae::ColliderData const &data) = 0;
        virtual glm::vec2 ModifyPushAmount(glm::vec2 const &normal);

        explicit BubbleState(BubbleComponent &owner);
        virtual ~BubbleState() = default;

    protected:
        BubbleComponent &m_owner;
    };
}

#endif //MINIGIN_IBUBBLESTATE_HPP
