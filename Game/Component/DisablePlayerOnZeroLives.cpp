#include "DisablePlayerOnZeroLives.hpp"

#include "FlickerComponent.hpp"
#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"
#include "PlayerAnimationComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Component/ColliderComponent.hpp"
#include "Component/PhysicsComponent.hpp"
#include "Component/TextureComponent.hpp"
#include "Event/Sdbm.hpp"

void game::DisablePlayerOnZeroLives::Start()
{
    GetGameObject().AddObserver(this);
}

void game::DisablePlayerOnZeroLives::Notify(uint32_t event, dae::ObserverData const* data)
{
    if (event != dae::sdbm_hash("lives_changed")) return;
    const auto liveChangeData{dynamic_cast<LiveChangedData const *>(data)};
    if (liveChangeData == nullptr) return;

    if (liveChangeData->newLives < 0) Disable();
}

game::DisablePlayerOnZeroLives::DisablePlayerOnZeroLives(dae::GameObject& owner)
    : GameComponent(owner)
{
}

void game::DisablePlayerOnZeroLives::Disable() const
{
    auto &self{GetGameObject()};

    self.GetComponent<dae::ColliderComponent>()->Enabled = false;
    self.GetComponent<dae::TextureComponent>()->Enabled = false;
    self.GetComponent<PhysicsComponent>()->Enabled = false;
    self.GetComponent<PlayerInputComponent>()->Enabled = false;
    self.GetComponent<FlickerComponent>()->Enabled = false;
    self.GetComponent<PlayerAnimationComponent>()->Enabled = false;
    self.GetComponent<LivesScoreComponent>()->Enabled = false;
}
