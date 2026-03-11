#include "MoveCommand.hpp"

#include "GameObject.hpp"
#include "Time.hpp"

void MoveCommand::Execute()
{
    m_object.SetLocalPosition(m_object.GetLocalTransform().GetPosition() + m_direction * m_speed * Time::get_delta_time());
}

MoveCommand::MoveCommand(float speed, dae::GameObject &gameObject, const glm::vec3 direction)
    : m_speed(speed)
    , m_object(gameObject)
    , m_direction(direction)
{
}
