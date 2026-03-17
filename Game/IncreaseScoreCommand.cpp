#include "IncreaseScoreCommand.hpp"

#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"

void game::IncreaseScoreCommand::Execute()
{
    if (m_scoreComponent == nullptr) return;

    m_scoreComponent->IncreaseScore(m_scoreToAdd);
}

game::IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject &object, int scoreToIncrease)    : m_scoreToAdd(scoreToIncrease),
      m_scoreComponent(object.GetComponent<LivesScoreComponent>())
{
    assert(m_scoreComponent != nullptr && "Unable to find score component!");
}
