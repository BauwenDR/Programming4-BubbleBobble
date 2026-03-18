#include "AchievementsComponent.hpp"

#include "LivesScoreComponent.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"
#include "SteamAchievements.hpp"

void game::AchievementsComponent::Start()
{
    m_livesScoreComponent = m_observingPlayer.GetComponent<LivesScoreComponent>();
    assert(m_livesScoreComponent != nullptr);
}

void game::AchievementsComponent::Notify(dae::GameObject&, uint32_t event)
{
    if (event != dae::sdbm_hash("ScoreChanged")) return;

    if (m_livesScoreComponent->GetScore() >= 500)
    {
#if USE_STEAMWORKS
        dae::SteamAchievements::GetInstance().SetAchievement("ACH_WIN_ONE_GAME");
#endif
    }
}

game::AchievementsComponent::AchievementsComponent(dae::GameObject &owner, dae::GameObject &player)
    : GameComponent(owner), m_observingPlayer(player)
{
}
