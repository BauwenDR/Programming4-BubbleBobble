#include "GameComponent.hpp"

namespace dae
{
    bool GameComponent::IsMarkedForDelete() const
    {
        return m_markedForDeletion;
    }

    GameObject &GameComponent::GetGameObject() const
    {
        return m_GameObject;
    }
}
