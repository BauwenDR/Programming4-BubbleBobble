#include "TimedKill.hpp"

#include "GameObject.hpp"
#include "Time.hpp"
#include "Event/Sdbm.hpp"

void game::TimedKill::Start()
{
}

void game::TimedKill::Update()
{
    m_timeLived += Time::timeDelta();

    float const livedPercentage{m_timeLived / m_timeToLive};
    if (livedPercentage > FLICKER_START_PERCENT)
    {
        GetGameObject().NotifyObservers(dae::sdbm_hash("enable_flicker"));
    }

    if (livedPercentage > 1.0f)
    {
        GetGameObject().MarkForDelete();
    }
}

game::TimedKill::TimedKill(dae::GameObject& owner, float timeToLive)
    : GameComponent(owner)
      , m_timeToLive(timeToLive)
{
}
