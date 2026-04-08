#include "LivesScoreComponent.hpp"

#include <format>

#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"

void game::LivesScoreComponent::DecreaseLives()
{
    m_lives = std::max(m_lives - 1, 0);

    GetGameObject().NotifyObservers(dae::sdbm_hash("PlayerDied"));
}

void game::LivesScoreComponent::IncreaseScore(int amount)
{
    m_score += amount;

    dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("ScoreChanged"));
    GetGameObject().NotifyObservers(dae::sdbm_hash("ScoreChanged"));
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
