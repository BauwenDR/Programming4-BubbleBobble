#include "GameObject.hpp"

#include "GameComponent.hpp"
#include "ResourceManager.hpp"

void dae::GameObject::MarkForDelete()
{
    m_markedForDelete = true;
}

bool dae::GameObject::IsMarkedForDelete() const
{
    return m_markedForDelete;
}

void dae::GameObject::Start() const
{
    for (const auto &component: m_components)
    {
        component->Start();
    }

    for (const auto &child: m_children)
    {
        child->Start();
    }
}

void dae::GameObject::Update() const
{
    for (const auto &component: m_components)
    {
        component->Update();
    }

    for (const auto &child: m_children)
    {
        child->Update();
    }
}

void dae::GameObject::PostUpdate()
{
    std::erase_if(m_components, [](const auto &component)
    {
        return component->IsMarkedForDelete();
    });

    for (const auto &child: m_children)
    {
        child->PostUpdate();
    }

    std::erase_if(m_children, [](const auto &child) { return child->IsMarkedForDelete(); });
}

void dae::GameObject::Render() const
{
    for (const auto &component: m_components)
    {
        component->Render();
    }

    for (const auto &child: m_children)
    {
        child->Render();
    }
}

dae::GameObject *dae::GameObject::GetParent() const
{
    return m_pParent;
}

void dae::GameObject::SetParent(GameObject *parent, bool keepWorldPosition)
{
    if (IsChild(parent) || parent == this || m_pParent == parent) return;

    if (parent == nullptr)
    {
        SetLocalPosition(GetWorldPosition());
    } else
    {
        if (keepWorldPosition)
        {
            SetLocalPosition(GetWorldPosition() - parent->GetWorldPosition());
        } else
        {
            SetPositionDirty();
        }
    }

    if (m_pParent)
    {
        m_pParent->RemoveChild(this);
    }
    m_pParent = parent;
    if (m_pParent)
    {
        m_pParent->AddChild(this);
    }
}

size_t dae::GameObject::GetChildCount() const
{
    return m_children.size();
}

dae::GameObject *dae::GameObject::GetChildAt(size_t index) const
{
    assert(index > 0 && index < m_children.size() && "GameObject GetAtIndex out of bounds");
    return m_children.at(index).get();
}

const glm::vec3 &dae::GameObject::GetWorldPosition()
{
    if (m_positionIsDirty)
    {
        UpdateWorldPosition();
    }

    return m_worldTransform.GetPosition();
}

void dae::GameObject::SetLocalPosition(const glm::vec3 &position)
{
    m_localTransform.SetPosition(position);
    SetPositionDirty();
}

void dae::GameObject::AddChild(GameObject *child)
{
    // This feels sketchy
    m_children.push_back(std::unique_ptr<GameObject>(child));
}

void dae::GameObject::RemoveChild(const GameObject *child)
{
    std::erase_if(m_children, [child](const auto &ptr) { return ptr.get() == child; });
}

bool dae::GameObject::IsChild(const GameObject *child) const
{
    return std::ranges::find_if(m_children, [child](const auto &ptr) { return ptr.get() == child; }) != m_children.end();
}

void dae::GameObject::UpdateWorldPosition()
{
    if (m_positionIsDirty)
    {
        if (m_pParent == nullptr)
        {
            m_worldTransform = m_localTransform;
        } else
        {
            m_worldTransform.SetPosition( m_pParent->GetWorldPosition() + m_localTransform.GetPosition());
        }
    }
    m_positionIsDirty = false;
}

void dae::GameObject::SetPositionDirty()
{
    m_positionIsDirty = true;

    for (const auto &child: m_children)
    {
        child->SetPositionDirty();
    }
}
