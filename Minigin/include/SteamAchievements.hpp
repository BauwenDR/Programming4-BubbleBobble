#ifndef MINIGIN_STEAMACHIEVEMENTS_HPP
#define MINIGIN_STEAMACHIEVEMENTS_HPP
#include "Singleton.hpp"

#if USE_STEAMWORKS
#ifdef _MSVC
#pragma warning (push)
#pragma warning (disable:4996)
#endif
#include <steam_api.h>
#ifdef _MSVC
#pragma warning (pop)
#endif

// Code taken from the Steam guide on implementing achievements
// https://partner.steamgames.com/doc/features/achievements/ach_guide

namespace dae
{
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }

    struct Achievement_t
    {
        int m_eAchievementID;
        const char *m_pchAchievementID;
        char m_rgchName[128];
        char m_rgchDescription[256];
        bool m_bAchieved;
        int m_iIconImage;
    };

    enum EAchievements
    {
        ACH_WIN_ONE_GAME = 0,
        ACH_WIN_100_GAMES = 1,
        ACH_TRAVEL_FAR_ACCUM = 2,
        ACH_TRAVEL_FAR_SINGLE = 3,
    };

    // Achievement array which will hold data about the achievements and their state
    constexpr Achievement_t g_Achievements[] =
    {
        _ACH_ID( ACH_WIN_ONE_GAME, "Winner" ),
        _ACH_ID( ACH_WIN_100_GAMES, "Champion" ),
        _ACH_ID( ACH_TRAVEL_FAR_ACCUM, "Interstellar" ),
        _ACH_ID( ACH_TRAVEL_FAR_SINGLE, "Orbiter" ),
    };


    class SteamAchievements final : public Singleton<SteamAchievements>
    {
    public:
        bool Initialize();
        bool SetAchievement(const char *ID);

        STEAM_CALLBACK(SteamAchievements, OnUserStatsStored, UserStatsStored_t, m_CallbackUserStatsStored);
        STEAM_CALLBACK(SteamAchievements, OnAchievementStored, UserAchievementStored_t, m_CallbackAchievementStored);

    private:
        friend class Singleton<dae::SteamAchievements>;
        SteamAchievements();

        uint64 m_iAppID; // Our current AppID
        const Achievement_t *m_pAchievements; // Achievements data
        int m_iNumAchievements; // The number of Achievements
        bool m_bInitialized; // Are we ready to use the API?
    };
}
#endif

#endif //MINIGIN_STEAMACHIEVEMENTS_HPP
