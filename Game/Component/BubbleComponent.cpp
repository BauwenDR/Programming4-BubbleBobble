#include "BubbleComponent.hpp"

#include "PlatformAiMovement.hpp"
#include "Time.hpp"
#include "BubbleState/AirCurrentState.hpp"
#include "BubbleState/FloatState.hpp"
#include "BubbleState/ShotState.hpp"
#include "BubbleState/StaticState.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/StagesManager.hpp"

void game::BubbleComponent::Start()
{
    GetGameObject().AddObserver(this);
}

void game::BubbleComponent::Update()
{
    m_currentState->Update();

    m_velocity *= Time::timeDelta();
    GetGameObject().SetLocalPosition(GetGameObject().GetLocalTransform().Position + glm::vec3{m_velocity, 0.0f});
}

// TODO pop bubbles that are nearby this one
void game::BubbleComponent::Pop() const
{
    GetGameObject().MarkForDelete();

    if (!m_hasTrappedEnemy) return;

    PickupPrefabData const data{.location = {GetGameObject().GetWorldPosition().x, GetGameObject().GetWorldPosition().y}, .worth = 500};
    StagesManager::GetInstance().SpawnPickup(data);
}

// TODO have bubbles push each-other
// TODO move state specific logic out of this function and delegate
void game::BubbleComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (!(event == dae::sdbm_hash("on_collision_enter") || event == dae::sdbm_hash("on_collision_exit"))) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() == dae::sdbm_hash("LEVEL_ROOF"))
    {
        m_isStuckToRoof = event == dae::sdbm_hash("on_collision_enter");
    }

    if (colliderData->collider->GetTag() == dae::sdbm_hash("STAGE") && colliderData->collisionNormal.y == 0.0f)
    {
        m_isInWall = event == dae::sdbm_hash("on_collision_enter");
    }

    if (colliderData->collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_LEFT") || colliderData->collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_RIGHT"))
    {
        m_isInAirCurrent = event == dae::sdbm_hash("on_collision_enter");
        m_isLeftCurrent = colliderData->collider->GetTag() == dae::sdbm_hash("WIND_CURRENT_LEFT");
    }

    // Vertical with player collision -> pop
    if (event == dae::sdbm_hash("on_collision_enter") && colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER") && colliderData->collisionNormal.x == 0.0f)
    {
        Pop();

        if (m_hasTrappedEnemy)
        {
            dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("enemy_died"));
        }
    }

    // Trap if in a trappable state
    if (!m_hasTrappedEnemy && event == dae::sdbm_hash("on_collision_enter") && colliderData->collider->GetTag() == dae::sdbm_hash("ENEMY") && m_currentState->CanTrapEnemy())
    {
        auto &collidedEnemy{colliderData->collider->GetGameObject()};
        collidedEnemy.MarkForDelete();
        collidedEnemy.GetComponent<PlatformAiMovement>()->enabled = false;
        collidedEnemy.GetComponent<PhysicsComponent>()->enabled = false;
        m_hasTrappedEnemy = true;
    }
}

game::BubbleComponent::BubbleComponent(dae::GameObject &owner, bool shotLeft)
    : GameComponent(owner)
      , m_currentState(std::make_unique<bubble::ShotState>(*this, shotLeft))
{
}

game::BubbleComponent::~BubbleComponent() = default;

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
