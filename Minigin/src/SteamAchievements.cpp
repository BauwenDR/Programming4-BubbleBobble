#include "SteamAchievements.hpp"

#include <iostream>
#include <ostream>

#if USE_STEAMWORKS
dae::SteamAchievements::SteamAchievements()
    : m_CallbackUserStatsStored(this, &SteamAchievements::OnUserStatsStored)
      , m_CallbackAchievementStored(this, &SteamAchievements::OnAchievementStored)
      , m_iAppID(0)
      , m_bInitialized(false)
{
    m_iAppID = SteamUtils()->GetAppID();
    m_pAchievements = g_Achievements;
    m_iNumAchievements = 4;
    m_bInitialized = Initialize();
}

bool dae::SteamAchievements::Initialize()
{
    // Is Steam loaded? If not we can't get stats.
    if ( nullptr == SteamUserStats() || nullptr == SteamUser() )
    {
        return false;
    }
    // Is the user logged on?  If not we can't access stats.
    if ( !SteamUser()->BLoggedOn() )
    {
        return false;
    }

    return true;
}

bool dae::SteamAchievements::SetAchievement(const char *ID)
{
    // Have we received a call back from Steam yet?
    if (m_bInitialized)
    {
        SteamUserStats()->SetAchievement(ID);
        return SteamUserStats()->StoreStats();
    }

    // If not then we can't set achievements yet
    return false;
}

void dae::SteamAchievements::OnUserStatsStored(UserStatsStored_t *pCallback)
{
    // we may get callbacks for other games' stats arriving, ignore them
    if ( m_iAppID == pCallback->m_nGameID )
    {
        if ( k_EResultOK == pCallback->m_eResult )
        {
            std::cout << "Stored Stats for Steam\n";
        }
        else
        {
            std::cerr << "StatsStored - failed, " << pCallback->m_eResult << '\n';
        }
    }
}

void dae::SteamAchievements::OnAchievementStored(UserAchievementStored_t *pCallback)
{
    // we may get callbacks for other games' stats arriving, ignore them
    if ( m_iAppID == pCallback->m_nGameID )
    {
        std::cout << "Stored Achievement for Steam\n";
    }
}
#endif
