#ifndef MINIGIN_MOVECOMMAND_HPP
#define MINIGIN_MOVECOMMAND_HPP

#include <glm/vec3.hpp>

#include "ICommand.hpp"

namespace dae
{
    class GameObject;
}

namespace game
{
    class MoveCommand final : public dae::ICommand
    {
    public:
        MoveCommand(dae::GameObject &objectToMove, float speed, const glm::vec3 &direction);
        void Execute() override;

    private:
        dae::GameObject &m_objectToMove;
        glm::vec3 m_moveDirection{};
        float m_moveSpeed{};
    };
}

#endif //MINIGIN_MOVECOMMAND_HPP