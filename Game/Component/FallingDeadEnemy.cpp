#include "FallingDeadEnemy.hpp"

#include "GameObject.hpp"
#include "PhysicsComponent.hpp"
#include "Event/Sdbm.hpp"

void game::FallingDeadEnemy::Start()
{
    m_physics = GetGameObject().GetComponent<game::PhysicsComponent>();
}

void game::FallingDeadEnemy::Update()
{
    m_physics->MoveHorizontal(m_movingLeft ? -1.0f : 1.0f);
}

void game::FallingDeadEnemy::Notify(uint32_t event, dae::ObserverData const *data)
{
    if (!(event == dae::sdbm_hash("has_landed") || event == dae::sdbm_hash("on_collision_enter"))) return;

    if (event == dae::sdbm_hash("has_landed"))
    {
        return;
    }

    if (data == nullptr) return;
    const auto colliderData{dynamic_cast<dae::ColliderData const *>(data)};
    if (colliderData == nullptr) return;

    if (colliderData->collider->GetTag() != dae::sdbm_hash("STAGE")) return;

    if (colliderData->collisionNormal.x != 0.0f)
    {
        m_movingLeft = !m_movingLeft;
    }
}

game::FallingDeadEnemy::FallingDeadEnemy(dae::GameObject &owner, bool movingLeft)
    : GameComponent(owner)
      , m_movingLeft(movingLeft)
{
}
