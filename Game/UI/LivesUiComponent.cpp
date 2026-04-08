#include "LivesUiComponent.hpp"

#include <format>

#include "Component/LivesScoreComponent.hpp"

#include "Component/TextComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"

void game::LivesUiComponent::Start()
{
    m_observingPlayer.AddObserver(this);

    m_textComponent = GetGameObject().GetComponent<dae::TextComponent>();
    assert(m_textComponent != nullptr);

    m_playerLivesComponent = m_observingPlayer.GetComponent<LivesScoreComponent>();
    assert(m_playerLivesComponent != nullptr);
}

void game::LivesUiComponent::Notify(dae::GameObject const &, uint32_t event, dae::ObserverData const *)
{
    if (event != dae::sdbm_hash("PlayerDied")) return;
    if (m_textComponent == nullptr) return;
    if (m_playerLivesComponent == nullptr) return;

    m_textComponent->SetText(std::format("# Lives: {}", m_playerLivesComponent->GetLives()));
}

game::LivesUiComponent::LivesUiComponent(dae::GameObject &owner, dae::GameObject &player)
: GameComponent(owner)
, m_observingPlayer(player)
{
}
