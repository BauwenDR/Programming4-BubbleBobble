#include "LivesScoreComponent.hpp"

#include "GameObject.hpp"
#include "PickupComponent.hpp"
#include "Time.hpp"
#include "Component/ColliderComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"

int game::LivesScoreComponent::GetScore() const
{
    return m_score;
}

void game::LivesScoreComponent::Start()
{
    GetGameObject().AddObserver(this);
}

void game::LivesScoreComponent::Update()
{
    if (m_invulnerabilityTimer > 0.0f)
    {
        m_invulnerabilityTimer -= Time::timeDelta();

        if (m_invulnerabilityTimer <= 0.0f)
        {
            GetGameObject().NotifyObservers(dae::sdbm_hash("disable_flicker"));
        }
    }
}

int32_t game::LivesScoreComponent::GetLives() const
{
    return m_lives;
}

game::LivesScoreComponent::LivesScoreComponent(dae::GameObject &owner)
    : GameComponent(owner)
{
}

void game::LivesScoreComponent::OnScoreChange(dae::ObserverData const *data)
{
    if (data == nullptr) return;
    const auto pickupData{dynamic_cast<PickupData const *>(data)};
    if (pickupData == nullptr) return;

    m_score += pickupData->worth;

    GetGameObject().NotifyObservers(dae::sdbm_hash("score_changed"));
    dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("score_changed"));
}

void game::LivesScoreComponent::OnEnemyCollision(dae::ObserverData const *data)
{
    if (m_invulnerabilityTimer > 0.0f) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() == dae::sdbm_hash("ENEMY"))
    {
        GetGameObject().NotifyObservers(dae::sdbm_hash("enable_flicker"));
        m_invulnerabilityTimer = INVULNERABILITY_TIME;
        --m_lives;

        LiveChangedData const liveData{false, m_lives};
        GetGameObject().NotifyObservers(dae::sdbm_hash("lives_changed"), &liveData);
        dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("player_died"));
    }
}

void game::LivesScoreComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (event == dae::sdbm_hash("on_pickup"))
    {
        OnScoreChange(data);
    }

    if (event == dae::sdbm_hash("on_collision_enter") || event == dae::sdbm_hash("on_collision_stay"))
    {
        OnEnemyCollision(data);
    }
}
