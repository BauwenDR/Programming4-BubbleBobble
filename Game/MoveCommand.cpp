#include "MoveCommand.hpp"

#include "GameObject.hpp"
#include "Time.hpp"

game::MoveCommand::MoveCommand(dae::GameObject &objectToMove, float speed, const glm::vec3 &direction)
    : m_objectToMove(objectToMove)
      , m_moveDirection(direction)
      , m_moveSpeed(speed)
{
}

void game::MoveCommand::Execute()
{
    const auto currentTransform{m_objectToMove.GetLocalTransform()};
    m_objectToMove.SetLocalPosition(currentTransform.GetPosition() + m_moveDirection * m_moveSpeed * Time::timeDelta());
}
