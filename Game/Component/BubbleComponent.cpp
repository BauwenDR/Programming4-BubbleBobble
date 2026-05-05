#include "BubbleComponent.hpp"

#include "PlatformAiMovement.hpp"
#include "BubbleState/AirCurrentState.hpp"
#include "BubbleState/FloatState.hpp"
#include "BubbleState/ShotState.hpp"
#include "BubbleState/StaticState.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/PrefabManager.hpp"

game::BubbleComponent::BubbleComponent(dae::GameObject &owner, bool shotLeft)
    : GameComponent(owner)
      , m_currentState(std::make_unique<bubble::ShotState>(*this, shotLeft))
{
}

void game::BubbleComponent::Update()
{
    m_currentState->Update();
}

void game::BubbleComponent::Pop() const
{
    PickupPrefabData const data{.location = {GetGameObject().GetWorldPosition().x, GetGameObject().GetWorldPosition().y}, .worth = 500};
    PrefabManager::GetInstance().SpawnPickup(data);
    GetGameObject().MarkForDelete();

    // TODO pop bubbles that are nearby this one
}

void game::BubbleComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (event != dae::sdbm_hash("on_collision_enter")) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    // Vertical with player collision -> pop
    if (colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER") && colliderData->collisionNormal.x == 0.0f)
    {
        Pop();
    }

    // Trap if in a trappable state
    if (colliderData->collider->GetTag() == dae::sdbm_hash("ENEMY") && m_currentState->CanTrapEnemy())
    {
        auto &collidedEnemy{colliderData->collider->GetGameObject()};
        collidedEnemy.SetParent(&GetGameObject(), false);
        collidedEnemy.GetComponent<PlatformAiMovement>()->enabled = false;
        collidedEnemy.GetComponent<PhysicsComponent>()->enabled = false;
        m_hasTrappedEnemy = true;
    }
}

void game::BubbleComponent::SwitchState(BubbleStates newState)
{
    switch (newState)
    {
        case BubbleStates::Static:
            m_currentState = std::make_unique<bubble::StaticState>(*this);
            break;
        case BubbleStates::AirCurrent:
            m_currentState = std::make_unique<bubble::AirCurrentState>(*this);
            break;
        case BubbleStates::Floating:
            m_currentState = std::make_unique<bubble::FloatState>(*this);
            break;
        case BubbleStates::Shot:
            m_currentState = std::make_unique<bubble::ShotState>(*this, false);
            break;
    }
}
