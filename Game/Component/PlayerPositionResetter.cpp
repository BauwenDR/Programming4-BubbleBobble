#include "PlayerPositionResetter.hpp"

#include "GameObject.hpp"
#include "LivesScoreComponent.hpp"
#include "PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"

void game::PlayerPositionResetter::Start()
{
    dae::EventManager::GetInstance().AttachHandler(dae::sdbm_hash("scene_manager_scene_switch"), this);
    GetGameObject().AddObserver(this);

    m_physics = GetGameObject().GetComponent<PhysicsComponent>();
    assert(m_physics != nullptr);
}

void game::PlayerPositionResetter::OnDelete()
{
    dae::EventManager::GetInstance().DetachHandler(this);
}

void game::PlayerPositionResetter::HandleEvent(uint32_t event)
{
    if (event != dae::sdbm_hash("scene_manager_scene_switch")) return;

    m_physics->ResetToStart();
}

void game::PlayerPositionResetter::Notify(uint32_t event, const dae::ObserverData* data)
{
    if (event != dae::sdbm_hash("lives_changed")) return;
    const auto liveChangeData{dynamic_cast<LiveChangedData const *>(data)};
    if (liveChangeData == nullptr) return;

    if (liveChangeData->isOneUp) return;

    m_physics->ResetToStart();
}

game::PlayerPositionResetter::PlayerPositionResetter(dae::GameObject& owner)
    : GameComponent(owner)
{
}
