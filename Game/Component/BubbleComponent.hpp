#ifndef MINIGIN_BUBBLECOMPONENT_HPP
#define MINIGIN_BUBBLECOMPONENT_HPP
#include <memory>
#include <glm/vec2.hpp>

#include "Component/GameComponent.hpp"

#include "Event/IObserver.hpp"

namespace game
{
    namespace bubble
    {
        class BubbleState;
        class FloatState;
        class ShotState;
        class AirCurrentState;
        class StaticState;
    }

    enum class BubbleStates : uint8_t
    {
        Static,
        Shot,
        Floating,
        AirCurrent
    };

    class BubbleComponent final : public dae::GameComponent, public dae::IObserver
    {
    public:

        void Start() override;
        void Update() override;

        void Pop() const;

        void Notify(uint32_t event, const dae::ObserverData *data) override;

        BubbleComponent(dae::GameObject &owner, bool shotLeft);
        ~BubbleComponent() override;
    private:
        friend class bubble::AirCurrentState;
        friend class bubble::FloatState;
        friend class bubble::ShotState;
        friend class bubble::StaticState;

        std::unique_ptr<bubble::BubbleState> m_currentState{};
        glm::vec2 m_velocity{};
        bool m_isInWall{};
        bool m_isInAirCurrent{};
        bool m_isLeftCurrent{};
        bool m_isStuckToRoof{};
        bool m_hasTrappedEnemy{};

        void SwitchState(BubbleStates newState);
    };
}

#endif //MINIGIN_BUBBLECOMPONENT_HPP
