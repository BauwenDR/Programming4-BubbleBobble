#ifndef MINIGIN_SPAWNBUBBLECOMMAND_HPP
#define MINIGIN_SPAWNBUBBLECOMMAND_HPP
#include "Event/ICommand.hpp"

namespace dae
{
    class GameObject;
}

namespace game {
    class PhysicsComponent;

    class SpawnBubbleCommand final : public dae::ICommand
    {
    public:
        void Execute() override;

        explicit SpawnBubbleCommand(dae::GameObject const *gameObject, PhysicsComponent const *physics);
        ~SpawnBubbleCommand() override = default;

    private:
        dae::GameObject const *m_gameObject{};
        PhysicsComponent const *m_physicsComponent{};
    };
}

#endif //MINIGIN_SPAWNBUBBLECOMMAND_HPP
