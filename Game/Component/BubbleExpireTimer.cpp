#include "BubbleExpireTimer.hpp"

#include "BubbleComponent.hpp"
#include "GameObject.hpp"
#include "Time.hpp"
#include "Component/TextureComponent.hpp"

void game::BubbleExpireTimer::Start()
{
    m_bubble = GetGameObject().GetComponent<BubbleComponent>();
    m_texture = GetGameObject().GetComponent<dae::TextureComponent>();
}

void game::BubbleExpireTimer::Update()
{
    m_timeLived += Time::timeDelta();

    float const livedPercentage{m_timeLived / m_timeToLive};
    if (livedPercentage >= DANGER_TIME_PERCENT)
    {
        if (m_currentOffset != DANGER_OFFSET)
        {
            m_texture->SetSpriteOffset(glm::vec2{DANGER_OFFSET, 0.0f});
            m_currentOffset = DANGER_OFFSET;
        }
    } else if (livedPercentage >= WARNING_TIME_PERCENT)
    {
        if (m_currentOffset != WARNING_OFFSET)
        {
            m_texture->SetSpriteOffset(glm::vec2{WARNING_OFFSET, 0.0f});
            m_currentOffset = WARNING_OFFSET;
        }
    }

    if (livedPercentage > 1.0f)
    {
        m_bubble->Release();
    }
}

game::BubbleExpireTimer::BubbleExpireTimer(dae::GameObject& owner, float timeToLive)
    : GameComponent(owner)
      , m_timeToLive(timeToLive)
{
}
