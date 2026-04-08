#include "LivesScoreComponent.hpp"

#include "GameObject.hpp"
#include "PickupComponent.hpp"
#include "Event/Sdbm.hpp"

int game::LivesScoreComponent::GetScore() const
{
    return m_score;
}

void game::LivesScoreComponent::Start()
{
    GetGameObject().AddObserver(this);
}

int game::LivesScoreComponent::GetLives() const
{
    return m_lives;
}

game::LivesScoreComponent::LivesScoreComponent(dae::GameObject &owner)
    : GameComponent(owner)
{
}

void game::LivesScoreComponent::Notify(const dae::GameObject &, uint32_t event, const dae::ObserverData *data)
{
    if (event != dae::sdbm_hash("pickup")) return;

    if (data == nullptr) return;
    const auto pickupData{dynamic_cast<PickupData const *>(data)};
    if (pickupData == nullptr) return;

    m_score += pickupData->worth;

    GetGameObject().NotifyObservers(dae::sdbm_hash("score_changed"), {});
}
