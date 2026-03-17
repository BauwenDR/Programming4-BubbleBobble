#include "LivesScoreComponent.hpp"

#include <format>

#include "EventManager.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"

void game::LivesScoreComponent::DecreaseLives()
{
    --m_lives;

    GetGameObject().NotifyObservers(dae::sdbm_hash("LIVES_CHANGED"));
}

void game::LivesScoreComponent::IncreaseScore(int amount)
{
    m_score += amount;

    GetGameObject().NotifyObservers(dae::sdbm_hash("SCORE_CHANGED"));
}

int game::LivesScoreComponent::GetScore() const
{
    return m_score;
}

void game::LivesScoreComponent::HandleEvent(uint32_t event)
{
    if (event == m_smallScoreEventId)
    {
        IncreaseScore(SMALL_SCORE_AMOUNT);
    }

    if (event == m_bigScoreEventId)
    {
        IncreaseScore(BIG_SCORE_AMOUNT);
    }
}

game::LivesScoreComponent::LivesScoreComponent(dae::GameObject &owner, const int playerNumber)
    : GameComponent(owner)
{
    // This is ugly; I know
    if (playerNumber == 0)
    {
        m_smallScoreEventId = dae::sdbm_hash("PLAYER_ONE_SMALL_PICKUP");
        m_bigScoreEventId = dae::sdbm_hash("PLAYER_ONE_BIG_PICKUP");
    } else
    {
        m_smallScoreEventId = dae::sdbm_hash("PLAYER_TWO_SMALL_PICKUP");
        m_bigScoreEventId = dae::sdbm_hash("PLAYER_TWO_BIG_PICKUP");
    }

    dae::EventManager::GetInstance().AttachHandler(m_smallScoreEventId, this);
    dae::EventManager::GetInstance().AttachHandler(m_bigScoreEventId, this);
}

game::LivesScoreComponent::~LivesScoreComponent()
{
    dae::EventManager::GetInstance().DetachHandler(this);
}

int game::LivesScoreComponent::GetLives() const
{
    return m_lives;
}
