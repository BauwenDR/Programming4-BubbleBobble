#include "GameComponent.hpp"

#include <cassert>

namespace dae
{
    bool GameComponent::IsMarkedForDelete() const
    {
        return m_markedForDeletion;
    }

    GameObject *GameComponent::GetGameObject() const
    {
        return m_pGameObject;
    }

    GameComponent::GameComponent(GameObject *owner) : m_pGameObject(owner)
    {
        assert(owner != nullptr && "A component must always have an owner");
    }
}
