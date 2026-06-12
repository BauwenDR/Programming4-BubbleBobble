#include "BubbleComponent.hpp"

#include <glm/gtx/norm.inl>

#include "CapturableComponent.hpp"
#include "SpawnPickupOnDeath.hpp"
#include "Time.hpp"
#include "BubbleState/AirCurrentState.hpp"
#include "BubbleState/FloatState.hpp"
#include "BubbleState/ShotState.hpp"
#include "BubbleState/StaticState.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/TextureComponent.hpp"
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

void game::BubbleComponent::Pop(glm::vec2 poppedFrom, int32_t popNumber)
{
    if (m_hasPopped) return;
    m_hasPopped = true;

    if (m_hasTrappedEnemy)
    {
        auto const trappedEnemy{GetGameObject().GetChildAt(0)};
        auto const captureComp{trappedEnemy->GetComponent<CapturableComponent>()};

        if (!captureComp) return;

        captureComp->OnPop(poppedFrom.x < m_collider->GetColliderCenter().x, popNumber);
        popNumber *= 2;
    }

    for (auto bubble: m_collidingBubbles)
    {
        bubble->Pop(poppedFrom, popNumber);
    }

    GetGameObject().MarkForDelete();
}

void game::BubbleComponent::Release()
{
    if (m_hasTrappedEnemy)
    {
        auto const trappedEnemy{GetGameObject().GetChildAt(0)};
        auto const captureComp{trappedEnemy->GetComponent<CapturableComponent>()};

        if (!captureComp) return;
        captureComp->OnRelease();
        trappedEnemy->SetLocalPosition(glm::vec3{0.0f, 0.0f, 0.0f});
        trappedEnemy->SetParent(nullptr, true);

        m_hasTrappedEnemy = false;
    }

    GetGameObject().MarkForDelete();
}

void game::BubbleComponent::Notify(uint32_t event, const dae::ObserverData *data)
{
    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    bool canInteract{m_currentState->CanPop()};
    if ((colliderData->collider->GetTag() == dae::sdbm_hash("BUBBLE") || colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER")) && canInteract)
    {
        BubblePushCollision(event, colliderData);
    }

    // TODO not a proper way of dealing with multiple walls
    if (colliderData->collider->GetTag() == dae::sdbm_hash("STAGE") && colliderData->collisionNormal.y == 0.0f)
    {
        m_isInWall = event == dae::sdbm_hash("on_collision_enter");
    }

    m_currentState->OnCollision(event, *colliderData);

    // Vertical with player collision -> pop
    if (
        event == dae::sdbm_hash("on_collision_stay") &&
        colliderData->collider->GetTag() == dae::sdbm_hash("PLAYER") &&
        colliderData->collisionNormal.x == 0.0f &&
        canInteract &&
        glm::distance2(m_collider->GetColliderCenter(), colliderData->collider->GetColliderCenter()) < 60.0f * 60.0f
    )
    {
        Pop(colliderData->collider->GetColliderCenter());
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
        case BubbleStates::DoNotChange:
            break;
    }
}

void game::BubbleComponent::BubblePushCollision(uint32_t event, dae::ColliderData const *colliderData)
{
    if (colliderData->collider->GetTag() == dae::sdbm_hash("BUBBLE"))
    {
        if (event == dae::sdbm_hash("on_collision_enter"))
        {
            m_collidingBubbles.emplace(colliderData->collider->GetGameObject().GetComponent<BubbleComponent>());
        }

        if (event == dae::sdbm_hash("on_collision_exit"))
        {
            m_collidingBubbles.erase(colliderData->collider->GetGameObject().GetComponent<BubbleComponent>());
        }
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
