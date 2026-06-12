#include "UI/LiveUiComponent.hpp"

#include "GameObject.hpp"
#include "Component/LivesScoreComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Render/ResourceManager.hpp"

void game::LiveUiComponent::Start()
{
    m_observingPlayer->AddObserver(this);

    auto const livesComp{m_observingPlayer->GetComponent<LivesScoreComponent>()};
    ResizeLiveComponents(livesComp->GetLives());
}

void game::LiveUiComponent::OnDelete()
{
    if (m_observingPlayer != nullptr) m_observingPlayer->RemoveObserver(this);
}

void game::LiveUiComponent::Notify(uint32_t event, dae::ObserverData const *data)
{
    if (event == dae::sdbm_hash("object_destroyed"))
    {
        m_observingPlayer = nullptr;
        return;
    }

    if (event != dae::sdbm_hash("lives_changed")) return;
    const auto liveChangeData{dynamic_cast<LiveChangedData const *>(data)};
    if (liveChangeData == nullptr) return;


    for (size_t index{0}; index < m_healthComponents.size(); ++index)
    {
        m_healthComponents.at(index)->Enabled = index < static_cast<size_t>(liveChangeData->newLives);
    }
}

game::LiveUiComponent::LiveUiComponent(dae::GameObject &owner, dae::GameObject *player, bool leftToRight)
: GameComponent(owner)
  , m_observingPlayer(player)
  , m_leftToRight(leftToRight)
{
}

void game::LiveUiComponent::ResizeLiveComponents(size_t lives)
{
    if (m_healthComponents.size() >= lives) return;

    for (size_t index{m_healthComponents.size()}; index < lives; ++index)
    {
        auto newComp{std::make_unique<dae::TextureComponent>(
            GetGameObject(),
            dae::ResourceManager::GetInstance().LoadTexture("Player/PlayerLives.png"),
            4.0f,
            glm::vec2{8.0f, 8.0f},
            glm::vec2{m_leftToRight ? 0.0f : 1.0f, 0.0f}
        )};
        newComp->RenderOffset.x = (m_leftToRight ? 32.0f : -32.0f) * static_cast<float>(index);

        m_healthComponents.emplace_back(newComp.get());
        GetGameObject().AddComponent(std::move(newComp));
    }
}
