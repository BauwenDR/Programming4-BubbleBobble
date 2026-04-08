#include "ScoreUiComponent.hpp"

#include <format>

#include "Component/LivesScoreComponent.hpp"

#include "Component/TextComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"

void game::ScoreUiComponent::Start()
{
    m_observingPlayer->AddObserver(this);

    m_textComponent = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_textComponent != nullptr);

    m_playerLivesComponent = m_observingPlayer->GetComponent<LivesScoreComponent>();
    assert(m_playerLivesComponent != nullptr);
}

void game::ScoreUiComponent::Notify(uint32_t event, const dae::ObserverData *)
{
    if (event == dae::sdbm_hash("object_destroyed"))
    {
        m_observingPlayer = nullptr;
        return;
    }

    if (event != dae::sdbm_hash("score_changed")) return;
    if (m_textComponent == nullptr) return;
    if (m_playerLivesComponent == nullptr) return;

    m_textComponent->SetText(std::format("{:09}", m_playerLivesComponent->GetScore()));
}

game::ScoreUiComponent::ScoreUiComponent(dae::GameObject &owner, dae::GameObject *player)
: GameComponent(owner)
, m_observingPlayer(player)
{
}

game::ScoreUiComponent::~ScoreUiComponent()
{
    if (m_observingPlayer != nullptr) m_observingPlayer->RemoveObserver(this);
}
