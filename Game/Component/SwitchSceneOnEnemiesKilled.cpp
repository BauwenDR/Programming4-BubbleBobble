#include "SwitchSceneOnEnemiesKilled.hpp"

#include "Time.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/StagesManager.hpp"

void game::SwitchSceneOnEnemiesKilled::Start()
{
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("enemy_died"), this);
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("level_reset"), this);
}

void game::SwitchSceneOnEnemiesKilled::Update()
{
    if (!m_canSwitch) return;

    m_switchCountdown -= Time::timeDelta();

    if (m_switchCountdown > 0.0f) return;

    StagesManager::GetInstance().LoadNextStageFromJson();
}

void game::SwitchSceneOnEnemiesKilled::HandleEvent(uint32_t event)
{
    if (event == dae::sdbm_hash("enemy_died"))
    {
        --m_remainingEnemies;

        if (m_remainingEnemies <= 0)
        {
            m_canSwitch = true;
            m_switchCountdown = SWITCH_DELAY;
        }
    }

    if (event == dae::sdbm_hash("level_reset"))
    {
        m_remainingEnemies = m_enemyThreshold;
    }
}

game::SwitchSceneOnEnemiesKilled::SwitchSceneOnEnemiesKilled(dae::GameObject &owner, int threshold)
    : GameComponent(owner)
      , m_enemyThreshold(threshold)
      , m_remainingEnemies(threshold)
{
}

game::SwitchSceneOnEnemiesKilled::~SwitchSceneOnEnemiesKilled()
{
    dae::EventManager::GetInstance().DetachHandler(this);
}
