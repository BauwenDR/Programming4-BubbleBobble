#include "IncreaseScoreCommand.hpp"

#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"
#include "Sdbm.hpp"

void game::IncreaseScoreCommand::Execute()
{
    if (m_scoreComponent == nullptr) return;

    if (m_isBig)
    {
        dae::EventManager::GetInstance().SendEvent(m_bigScoreEventId);
    } else
    {
        dae::EventManager::GetInstance().SendEvent(m_smallScoreEventId);
    }
}

game::IncreaseScoreCommand::IncreaseScoreCommand(dae::GameObject &object, int player, bool isBig)
    : m_scoreComponent(object.GetComponent<LivesScoreComponent>())
      , m_isBig(isBig)
{
    assert(m_scoreComponent != nullptr && "Unable to find score component!");

    if (player == 0)
    {
        m_smallScoreEventId = dae::sdbm_hash("PLAYER_ONE_SMALL_PICKUP");
        m_bigScoreEventId = dae::sdbm_hash("PLAYER_ONE_BIG_PICKUP");
    } else
    {
        m_smallScoreEventId = dae::sdbm_hash("PLAYER_TWO_SMALL_PICKUP");
        m_bigScoreEventId = dae::sdbm_hash("PLAYER_TWO_BIG_PICKUP");
    }
}
