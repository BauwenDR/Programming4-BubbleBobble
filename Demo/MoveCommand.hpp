#ifndef MINIGIN_MOVECOMMAND_HPP
#define MINIGIN_MOVECOMMAND_HPP
#include <glm/vec3.hpp>

#include "ICommand.hpp"

namespace dae
{
    class GameObject;
}

class MoveCommand final : public ICommand
{
public:

    void Execute() override;

    MoveCommand(float speed, dae::GameObject &gameObject, glm::vec3 direction);
    ~MoveCommand() override = default;

private:
    const float m_speed{};
    dae::GameObject &m_object;
    glm::vec3 m_direction{};
};



#endif //MINIGIN_MOVECOMMAND_HPP