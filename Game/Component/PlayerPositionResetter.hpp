#ifndef MINIGIN_PLAYERPOSITIONRESETTER_HPP
#define MINIGIN_PLAYERPOSITIONRESETTER_HPP
#include "Component/GameComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class PhysicsComponent;

    class PlayerPositionResetter final : public dae::GameComponent, public dae::IEventHandler, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override {}
        void OnDelete() override;

        void HandleEvent(uint32_t event) override;
        void Notify(uint32_t event, const dae::ObserverData* data) override;

        explicit PlayerPositionResetter(dae::GameObject &owner);
        ~PlayerPositionResetter() override = default;

    private:
        PhysicsComponent *m_physics{};
    };
}

#endif //MINIGIN_PLAYERPOSITIONRESETTER_HPP
