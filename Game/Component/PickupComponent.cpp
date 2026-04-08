#include "PickupComponent.hpp"

#include "Component/ColliderComponent.hpp"
#include "Event/Sdbm.hpp"
#include "GameObject.hpp"

void game::PickupComponent::Start()
{
    GetGameObject().AddObserver(this);
}

void game::PickupComponent::Notify(const dae::GameObject &, uint32_t event, dae::ObserverData const *data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() != dae::sdbm_hash("PLAYER")) return;

    const PickupData pickupData{m_worth};
    colliderData->collider->GetGameObject().NotifyObservers(dae::sdbm_hash("pickup"), &pickupData);
    GetGameObject().MarkForDelete();
}

game::PickupComponent::PickupComponent(dae::GameObject &owner, int worth)
    : GameComponent(owner)
      , m_worth(worth)
{
}

game::PickupComponent::~PickupComponent()
{
    GetGameObject().RemoveObserver(this);
}
