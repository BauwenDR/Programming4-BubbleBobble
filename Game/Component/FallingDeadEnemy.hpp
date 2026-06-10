#ifndef MINIGIN_JUMPONSPAWN_HPP
#define MINIGIN_JUMPONSPAWN_HPP
#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace game
{
    class PhysicsComponent;

    class FallingDeadEnemy final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;

        void Notify(uint32_t event, dae::ObserverData const *data) override;

        FallingDeadEnemy(dae::GameObject &owner, bool movingLeft);

    private:
        PhysicsComponent* m_physics{};

        bool m_movingLeft{};
    };
}

#endif //MINIGIN_JUMPONSPAWN_HPP
