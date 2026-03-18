#include "AchievementsComponent.hpp"

#include "LivesScoreComponent.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"
#include "SteamAchievements.hpp"

void game::AchievementsComponent::Notify(dae::GameObject& gameObject, uint32_t event)
{
    if (event != dae::sdbm_hash("ScoreChanged")) return;

    LivesScoreComponent* scoreComponent{gameObject.GetComponent<LivesScoreComponent>()};

    if (scoreComponent == nullptr) return;

    if (scoreComponent->GetScore() >= 500)
    {
#if USE_STEAMWORKS
        dae::SteamAchievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
#endif
    }
}

game::AchievementsComponent::AchievementsComponent(dae::GameObject& owner, const std::vector<dae::GameObject *> &players)
    : GameComponent(owner), m_players(players)
{
    for (const auto player: m_players)
    {
        player->AddObserver(this);
    }
}

game::AchievementsComponent::~AchievementsComponent()
{
    for (const auto player : m_players)
    {
        player->RemoveObserver(this);
    }
}
