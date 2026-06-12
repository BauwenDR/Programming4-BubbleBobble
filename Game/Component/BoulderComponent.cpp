#include "BoulderComponent.hpp"

#include "GameObject.hpp"
#include "Time.hpp"
#include "Component/ColliderComponent.hpp"
#include "Event/Sdbm.hpp"

void game::BoulderComponent::Start()
{
    GetGameObject().AddObserver(this);
}

void game::BoulderComponent::Update()
{
    auto newPosition{GetGameObject().GetLocalTransform().Position};
    newPosition.x += m_isMovingLeft ? -1.0f : 1.0f * BOULDER_SPEED * Time::timeDelta();
    GetGameObject().SetLocalPosition(newPosition);
}

void game::BoulderComponent::Notify(uint32_t event, dae::ObserverData const* data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (
        colliderData->collider->GetTag() != dae::sdbm_hash("STAGE") &&
        colliderData->collider->GetTag() != dae::sdbm_hash("PLAYER")
    ) return;

    GetGameObject().MarkForDelete();
}

game::BoulderComponent::BoulderComponent(dae::GameObject& owner, bool moveLeft)
    : GameComponent(owner)
      , m_isMovingLeft(moveLeft)
{
}
