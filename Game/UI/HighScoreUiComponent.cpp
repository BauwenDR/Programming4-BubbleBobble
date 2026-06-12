#include "HighScoreUiComponent.hpp"

#include <format>

#include "GameObject.hpp"
#include "GameState.hpp"
#include "Component/TextComponent.hpp"
#include "Event/Sdbm.hpp"

void game::HighScoreUiComponent::Start()
{
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("new_high_score"), this);

    m_textComponent = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_textComponent);

    m_textComponent->SetText(std::format("{:09}", GameState::GetInstance().HighScore));
}

void game::HighScoreUiComponent::OnDelete()
{
    dae::EventManager::GetInstance().DetachHandler(this);
}

void game::HighScoreUiComponent::HandleEvent(uint32_t event)
{
    if (event != dae::sdbm_hash("new_high_score")) return;

    m_textComponent->SetText(std::format("{:09}", GameState::GetInstance().HighScore));
}

game::HighScoreUiComponent::HighScoreUiComponent(dae::GameObject& owner)
    : GameComponent(owner)
{
}
