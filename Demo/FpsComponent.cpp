#include "FpsComponent.hpp"

#include <format>

#include "GameObject.hpp"
#include "TextComponent.hpp"
#include "Time.hpp"

void FpsComponent::Start([[maybe_unused]] dae::GameObject &object)
{
    m_text_component = object.GetComponent<dae::TextComponent>();
}

void FpsComponent::Update([[maybe_unused]] dae::GameObject &object)
{
    if (m_text_component)
    {
        m_text_component->set_text(std::format("FPS: {:.1f}", Time::get_frame_rate()));
    }
}

void FpsComponent::Render([[maybe_unused]] const dae::GameObject &object) const
{
}
