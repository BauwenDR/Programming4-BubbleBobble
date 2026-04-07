#ifndef MINIGIN_GRAVITYCOMPONENT_HPP
#define MINIGIN_GRAVITYCOMPONENT_HPP

#include "ColliderComponent.hpp"
#include "GameComponent.hpp"
#include "IObserver.hpp"

namespace dae
{
    class GravityComponent final : public GameComponent, public IObserver
    {
    public:
        void Start() override;
        void Update() override;
        void Render() const override {}

        void Jump();

        void Notify(const GameObject &object, uint32_t event, const ObserverData *data) override;

        explicit GravityComponent(GameObject &owner) : GameComponent(owner) {};
        ~GravityComponent() override = default;
    private:
        constexpr static float GRAVITY_FORCE{12.0f * 4};
        constexpr static float TerminalVelocity{20.0f * 4};

        ColliderComponent *m_collider{};

        float m_velY{};
        bool m_isOnGround{};
    };
}

#endif //MINIGIN_GRAVITYCOMPONENT_HPP
