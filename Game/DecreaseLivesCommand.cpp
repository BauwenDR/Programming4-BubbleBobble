#include "DecreaseLivesCommand.hpp"

#include "GameObject.hpp"

void game::DecreaseLivesCommand::Execute()
{
    if (m_livesComponent == nullptr) return;

    m_livesComponent->DecreaseLives();
}

game::DecreaseLivesCommand::DecreaseLivesCommand(dae::GameObject &object)
    : m_livesComponent(object.GetComponent<LivesScoreComponent>())
{
    assert(m_livesComponent != nullptr && "Unable to find lives component!");
}
