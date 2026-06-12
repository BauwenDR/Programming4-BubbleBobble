#include "CapturableComponent.hpp"

#include "AnimationComponent.hpp"
#include "GameObject.hpp"
#include "PlatformAiMovement.hpp"
#include "SpawnPickupOnDeath.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/Prefabs.hpp"
#include "Prefab/StagesManager.hpp"

void game::CapturableComponent::Update()
{
}

game::CapturableComponent::CapturableComponent(dae::GameObject& owner, glm::vec2 poppedSpriteOffset, bool isEnemy)
    : GameComponent(owner)
      , m_poppedEnemySpriteOffset(poppedSpriteOffset)
      , m_isEnemy(isEnemy)
{
}

void game::CapturableComponent::OnCapture() const
{
    auto &collidedEnemy{GetGameObject()};
    collidedEnemy.GetComponent<PlatformAiMovement>()->Enabled = false;
    collidedEnemy.GetComponent<AnimationComponent>()->Enabled = false;
    collidedEnemy.GetComponent<PhysicsComponent>()->Enabled = false;
    collidedEnemy.GetComponent<dae::ColliderComponent>()->Enabled = false;
    collidedEnemy.SetLocalScale(0.75f);
}

void game::CapturableComponent::OnRelease() const
{
    auto &self{GetGameObject()};
    self.GetComponent<PlatformAiMovement>()->Enabled = true;
    self.GetComponent<AnimationComponent>()->Enabled = true;
    self.GetComponent<PhysicsComponent>()->Enabled = true;
    self.GetComponent<dae::ColliderComponent>()->Enabled = true;
    self.SetLocalScale(1.0f);
}

void game::CapturableComponent::OnPop(bool flyLeft, int32_t popNumber) const
{
    auto &trappedEnemy{GetGameObject()};
    trappedEnemy.GetComponent<SpawnPickupOnDeath>()->PopMultiplier = popNumber;
    trappedEnemy.GetComponent<dae::TextureComponent>()->Enabled = false;

    if (m_isEnemy)
    {
        ProjectilePrefabData const pickupData{glm::vec2{GetGameObject().GetWorldPosition()}, flyLeft};
        auto const pickupObj{StagesManager::GetInstance().SpawnDeadEnemy(pickupData, m_poppedEnemySpriteOffset)};
        trappedEnemy.SetParent(pickupObj, false);

        dae::EventManager::GetInstance().SendEvent(dae::sdbm_hash("enemy_died"));
    }
}
