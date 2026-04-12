#ifndef MINIGIN_PLATFORMAIMOVEMENT_HPP
#define MINIGIN_PLATFORMAIMOVEMENT_HPP

#include <cstdint>

#include "Component/GameComponent.hpp"
#include "Event/IObserver.hpp"

namespace dae
{
    class PhysicsComponent;
}

namespace game
{
    enum class PlatformAiAction : uint8_t
    {
        None,
        WalkingLeft,
        WalkingRight,
        Jumping
    };

    class PlatformAiMovement final : public dae::GameComponent, public dae::IObserver
    {
    public:
        void Start() override;
        void Update() override;

        void Notify(uint32_t event, dae::ObserverData const *data) override;

        explicit PlatformAiMovement(dae::GameObject &owner, PlatformAiAction initialAction);
        ~PlatformAiMovement() override = default;

    private:
        constexpr static float DECISION_TIMEOUT{1.0f};

        dae::PhysicsComponent *m_physics{};
        PlatformAiAction m_currentAction{};

        float m_decisionCooldown{};

        bool m_overlappingPotentialJumpZone{false};

        void TakeNextMovementDecision();
    };
}


#endif //MINIGIN_PLATFORMAIMOVEMENT_HPP