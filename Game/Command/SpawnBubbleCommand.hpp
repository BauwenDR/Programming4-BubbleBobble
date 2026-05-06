#ifndef MINIGIN_SPAWNBUBBLECOMMAND_HPP
#define MINIGIN_SPAWNBUBBLECOMMAND_HPP
#include "Event/ICommand.hpp"

namespace game
{
    class PhysicsComponent;
}

namespace dae
{
    class GameObject;
}

class SpawnBubbleCommand final : public dae::ICommand
{
public:
    void Execute() override;

    explicit SpawnBubbleCommand(dae::GameObject const *gameObject, game::PhysicsComponent const *physics);
    ~SpawnBubbleCommand() override = default;

private:
    dae::GameObject const *m_gameObject{};
    game::PhysicsComponent const *m_physicsComponent{};
    bool m_wasMovingLeft{};
};

#endif //MINIGIN_SPAWNBUBBLECOMMAND_HPP
