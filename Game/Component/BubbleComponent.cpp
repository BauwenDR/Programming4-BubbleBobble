#include "BubbleComponent.hpp"

#include "PlatformAiMovement.hpp"
#include "Time.hpp"
#include "BubbleState/AirCurrentState.hpp"
#include "BubbleState/FloatState.hpp"
#include "BubbleState/ShotState.hpp"
#include "BubbleState/StaticState.hpp"
#include "Component/ColliderComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/StagesManager.hpp"

void game::BubbleComponent::Start()
{
    GetGameObject().AddObserver(this);
}

void game::BubbleComponent::Update()
{
    SwitchState(m_currentState->Update());

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
void game::BubbleComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (!(event == dae::sdbm_hash("on_collision_enter") || event == dae::sdbm_hash("on_collision_exit"))) return;

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    m_currentState->OnCollision(event, *colliderData);

    // Vertical with player collision -> pop
    if (event == dae::sdbm_hash("on_collision_enter") && colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER") && colliderData->collisionNormal.x == 0.0f)
    {
        Pop();

        if (m_hasTrappedEnemy)
        {
            dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("enemy_died"));
        }
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
        case BubbleStates::DoNotSwitch:
            break;
    }
}
