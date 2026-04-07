#include "JumpCommand.hpp"

#include "GravityComponent.hpp"

void JumpCommand::Execute()
{
    m_gravityComponent.Jump();
}
