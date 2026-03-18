#include "IncreaseScoreCommand.hpp"

#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"

void game::IncreaseScoreCommand::Execute()
{
    if (m_scoreComponent == nullptr) return;

    if (m_isBig)
    {
        m_scoreComponent->IncreaseScore(BIG_SCORE_AMOUNT);
    } else
    {
        m_scoreComponent->IncreaseScore(SMALL_SCORE_AMOUNT);
    }
}

game::IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject &object, bool isBig)
    : m_scoreComponent(object.GetComponent<LivesScoreComponent>())
      , m_isBig(isBig)
{
    assert(m_scoreComponent != nullptr && "Unable to find score component!");
}
