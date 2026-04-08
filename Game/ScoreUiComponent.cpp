#include "ScoreUiComponent.hpp"

#include <format>

#include "LivesScoreComponent.hpp"

#include "Component/TextComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"

void game::ScoreUiComponent::Start()
{
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("ScoreChanged"), this);

    m_textComponent = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_textComponent != nullptr);

    m_playerLivesComponent = m_observingPlayer.GetComponent<LivesScoreComponent>();
    assert(m_playerLivesComponent != nullptr);
}

void game::ScoreUiComponent::HandleEvent(uint32_t event)
{
    if (event != dae::sdbm_hash("ScoreChanged")) return;
    if (m_textComponent == nullptr) return;
    if (m_playerLivesComponent == nullptr) return;

    m_textComponent->SetText(std::format("Score: {}", m_playerLivesComponent->GetScore()));
}

game::ScoreUiComponent::ScoreUiComponent(dae::GameObject &owner, dae::GameObject &player)
: GameComponent(owner)
, m_observingPlayer(player)
{
}

game::ScoreUiComponent::~ScoreUiComponent()
{
    dae::EventManager::GetInstance().DetachHandler(this);
}
