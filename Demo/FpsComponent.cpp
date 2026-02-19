#include "FpsComponent.hpp"

#include <format>

#include "GameObject.hpp"
#include "TextComponent.hpp"
#include "Time.hpp"

namespace demo
{
    void FpsComponent::Start()
    {
        m_textComponent = GetGameObject()->GetComponent<dae::TextComponent>();
    }

    void FpsComponent::Update()
    {
        if (!m_textComponent) return;

        m_elapsedTime += Time::get_delta_time();
        m_passedFrames++;

        if (m_elapsedTime > RefreshThreshold)
        {
            const float frameRate = static_cast<float>(m_passedFrames) / m_elapsedTime;
            m_textComponent->SetText(std::format("FPS: {:.1f}", frameRate));

            m_elapsedTime = 0.0f;
            m_passedFrames = 0;
        }
    }
}
