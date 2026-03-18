#include "LivesScoreComponent.hpp"

#include <format>

#include "EventManager.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"

void game::LivesScoreComponent::DecreaseLives()
{
    m_lives = std::max(m_lives - 1, 0);

    GetGameObject().NotifyObservers(dae::sdbm_hash("LIVES_CHANGED"));
}

void game::LivesScoreComponent::IncreaseScore(int amount)
{
    m_score += amount;

    dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("SCORE_CHANGED"));
}

int game::LivesScoreComponent::GetScore() const
{
    return m_score;
}


game::LivesScoreComponent::LivesScoreComponent(dae::GameObject &owner)
    : GameComponent(owner)
{
}

int game::LivesScoreComponent::GetLives() const
{
    return m_lives;
}
