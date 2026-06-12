#include "CapturableComponent.hpp"

#include "AnimationComponent.hpp"
#include "AttackIfPlayerAtSameHeight.hpp"
#include "GameObject.hpp"
#include "PlatformAiMovement.hpp"
#include "PlayerInputComponent.hpp"
#include "SpawnPickupOnDeath.hpp"
#include "WrapAroundScreenComponent.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/EventManager.hpp"
#include "Event/Sdbm.hpp"
#include "Prefab/Prefabs.hpp"
#include "Prefab/StagesManager.hpp"

game::CapturableComponent::CapturableComponent(dae::GameObject& owner, glm::vec2 poppedSpriteOffset, bool isEnemy)
    : GameComponent(owner)
      , m_poppedEnemySpriteOffset(poppedSpriteOffset)
      , m_isEnemy(isEnemy)
{
}

void game::CapturableComponent::OnCapture() const
{
    auto &self{GetGameObject()};

    auto const platformMovement{self.GetComponent<PlatformAiMovement>()};
    auto const playerInput{self.GetComponent<PlatformAiMovement>()};
    auto const enemyAttack{self.GetComponent<AttackIfPlayerAtSameHeight>()};

    if (platformMovement) platformMovement->Enabled = false;
    if (playerInput) playerInput->Enabled = false;
    if (enemyAttack) enemyAttack->Enabled = false;

    self.GetComponent<AnimationComponent>()->Enabled = false;
    self.GetComponent<PhysicsComponent>()->Enabled = false;
    self.GetComponent<dae::ColliderComponent>()->Enabled = false;
    self.SetLocalScale(0.75f);
}

void game::CapturableComponent::OnRelease() const
{
    auto &self{GetGameObject()};
    auto const platformMovement{self.GetComponent<PlatformAiMovement>()};
    auto const playerInput{self.GetComponent<PlatformAiMovement>()};
    auto const enemyAttack{self.GetComponent<AttackIfPlayerAtSameHeight>()};

    if (platformMovement)
    {
        platformMovement->Enabled = true;
        platformMovement->ResetMovement();
    }
    if (playerInput) playerInput->Enabled = true;
    if (enemyAttack) enemyAttack->Enabled = true;

    self.GetComponent<AnimationComponent>()->Enabled = true;
    self.GetComponent<PhysicsComponent>()->Enabled = true;
    self.GetComponent<PhysicsComponent>()->ResetMovement();
    self.GetComponent<dae::ColliderComponent>()->Enabled = true;
    self.SetLocalScale(1.0f);

    self.NotifyObservers(dae::sdbm_hash("on_release"));
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
