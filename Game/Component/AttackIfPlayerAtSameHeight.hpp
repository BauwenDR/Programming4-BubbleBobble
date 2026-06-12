#ifndef MINIGIN_ATTACKIFPLAYERATSAMEHEIGHT_H
#define MINIGIN_ATTACKIFPLAYERATSAMEHEIGHT_H
#include "Component/GameComponent.hpp"

namespace game
{
    class PhysicsComponent;

    class AttackIfPlayerAtSameHeight final : public dae::GameComponent
    {
    public:
        void Start() override;
        void Update() override;

        explicit AttackIfPlayerAtSameHeight(dae::GameObject &owner);

    private:
        constexpr static float ATTACK_DELAY{2.2f};

        PhysicsComponent const *m_physics{};

        float m_attackDelay{};
    };
}

#endif //MINIGIN_ATTACKIFPLAYERATSAMEHEIGHT_H
