#include "GameComponent.hpp"

namespace dae
{
    bool GameComponent::IsMarkedForDelete() const
    {
        return m_markedForDeletion;
    }

    void GameComponent::MarkForDelete()
    {
        m_markedForDeletion = true;
    }

    GameObject &GameComponent::GetGameObject() const
    {
        return m_GameObject;
    }
}
