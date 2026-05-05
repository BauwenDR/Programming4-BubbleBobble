#ifndef MINIGIN_IBUBBLESTATE_HPP
#define MINIGIN_IBUBBLESTATE_HPP

namespace game
{
    class BubbleComponent;
}

namespace game::bubble
{
    class BubbleState
    {
    public:
        virtual void Update() = 0;
        virtual bool CanTrapEnemy() = 0;

        explicit BubbleState(BubbleComponent &owner);
        virtual ~BubbleState() = default;

    protected:
        BubbleComponent &m_owner;
    };
}

#endif //MINIGIN_IBUBBLESTATE_HPP
