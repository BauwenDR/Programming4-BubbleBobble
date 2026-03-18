#include "ScoreUiComponent.hpp"

#include <format>

#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"
#include "TextComponent.hpp"
#include "Sdbm.hpp"

void game::ScoreUiComponent::Start()
{
    m_observingPlayer.AddObserver(this);

    m_textComponent = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_textComponent != nullptr);

    m_playerLivesComponent = m_observingPlayer.GetComponent<LivesScoreComponent>();
    assert(m_playerLivesComponent != nullptr);
}

void game::ScoreUiComponent::Notify(dae::GameObject&, uint32_t event)
{
    if (event != dae::sdbm_hash("SCORE_CHANGED")) return;
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
    m_observingPlayer.RemoveObserver(this);
}
