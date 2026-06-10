#include "BubbleComponent.hpp"

#include <glm/gtx/norm.inl>

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
    m_collider = GetGameObject().GetComponent<dae::ColliderComponent>();
}

void game::BubbleComponent::Update()
{
    SwitchState(m_currentState->Update());

    m_velocity *= Time::timeDelta();
    GetGameObject().SetLocalPosition(GetGameObject().GetLocalTransform().Position + glm::vec3{m_velocity, 0.0f});
}

void game::BubbleComponent::Pop(int32_t popNumber)
{
    if (m_hasPopped) return;
    m_hasPopped = true;

    GetGameObject().MarkForDelete();

    for (auto bubble: m_collidingBubbles)
    {
        bubble->Pop(popNumber + 1);
    }

    if (!m_hasTrappedEnemy) return;

    // GetGameObject().GetChildAt(0)->GetComponent<>();
    dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("enemy_died"));
    PickupPrefabData const data{.location = {GetGameObject().GetWorldPosition().x, GetGameObject().GetWorldPosition().y}, .worth = 500 * popNumber};
    StagesManager::GetInstance().SpawnPickup(data);
}

void game::BubbleComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() == dae::sdbm_hash("BUBBLE"))
    {
        OnBubbleCollision(event, colliderData);
        return;
    }

    m_currentState->OnCollision(event, *colliderData);


    // Vertical with player collision -> pop
    if (
        event == dae::sdbm_hash("on_collision_stay") &&
        colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER") &&
        std::abs(colliderData->normal.y) > 0.3f &&
        m_currentState->CanPop() &&
        glm::distance2(m_collider->GetColliderCenter(), colliderData->collider->GetColliderCenter()) < 32.0f * 32.0f
    )
    {
        Pop();
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

void game::BubbleComponent::OnBubbleCollision(uint32_t event, dae::ColliderData const *colliderData)
{
    if (event == dae::sdbm_hash("on_collision_enter"))
    {
        m_collidingBubbles.emplace(colliderData->collider->GetGameObject().GetComponent<BubbleComponent>());
    }

    if (event == dae::sdbm_hash("on_collision_exit"))
    {
        m_collidingBubbles.erase(colliderData->collider->GetGameObject().GetComponent<BubbleComponent>());
    }

    if (event == dae::sdbm_hash("on_collision_stay"))
    {
        constexpr static float MAX_PUSH_DISTANCE{58.0f};
        constexpr static float MIN_DISTANCE_FACTOR{0.1f};

        float const dist{glm::distance(m_collider->GetColliderCenter(), colliderData->collider->GetColliderCenter())};
        float const t = glm::clamp(dist / MAX_PUSH_DISTANCE, 0.0f, 1.0f);
        float const distanceFactor = glm::mix(1.0f, MIN_DISTANCE_FACTOR, t);

        glm::vec2 const basePush{m_currentState->ModifyPushAmount(colliderData->normal) * distanceFactor};

        auto pushPosition = GetGameObject().GetLocalTransform().Position;
        pushPosition += glm::vec3(basePush, 0.0f) * PUSH_FORCE * Time::timeDelta();
        GetGameObject().SetLocalPosition(pushPosition);
    }
}
