#ifndef MINIGIN_SPAWNPROJECTILE_HPP
#define MINIGIN_SPAWNPROJECTILE_HPP
#include "Event/ICommand.hpp"

namespace dae
{
    class GameObject;
}

namespace game {
    class PhysicsComponent;

    class SpawnProjectileCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        explicit SpawnProjectileCommand(dae::GameObject const *gameObject, PhysicsComponent const *physics, bool m_isBoulder);
        ~SpawnProjectileCommand() override = default;

    private:
        dae::GameObject const *m_gameObject{};
        PhysicsComponent const *m_physicsComponent{};

        bool m_isBoulder{};
    };
}

#endif //MINIGIN_SPAWNPROJECTILE_HPP
