#include "GameObject.hpp"

#include "SceneManager.hpp"
#include "Component/GameComponent.hpp"
#include "Event/Sdbm.hpp"
#include "Render/ResourceManager.hpp"

void dae::GameObject::MarkForDelete()
{
    m_markedForDelete = true;

    for (const auto &child: m_children)
    {
        child->MarkForDelete();
    }
}

bool dae::GameObject::IsMarkedForDelete() const
{
    return m_markedForDelete;
}

dae::GameObject::GameObject()
    : m_localTransform(std::make_unique<Transform>())
      , m_worldTransform(std::make_unique<Transform>())
      , m_positionIsDirty(true)
{
}

dae::GameObject::~GameObject()
{
    for (const auto &component: m_components)
    {
        component->OnDelete();
    }

    const ObjectDestroyedData data(this);
    NotifyObservers(sdbm_hash("object_destroyed"), &data);
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
        if (component->Enabled) component->Update();
    }

    for (const auto &child: m_children)
    {
        child->Update();
    }
}

void dae::GameObject::LateUpdate() const
{
    for (const auto &component: m_components)
    {
        if (component->Enabled) component->LateUpdate();
    }

    for (const auto &child: m_children)
    {
        child->LateUpdate();
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
        if (component->Enabled) component->Render();
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

    std::unique_ptr<GameObject> thisPointer{};
    // Get moveable version of self and move to parent (or scene if new parent is nullptr)
    if (m_pParent != nullptr)
    {
        thisPointer = m_pParent->RemoveChild(this);
    } else
    {
        thisPointer = SceneManager::GetInstance().GetActive()->Remove(this);
    }
    if (parent != nullptr)
    {
        parent->AddChild(std::move(thisPointer));
        m_pParent = parent;
    }
}

size_t dae::GameObject::GetChildCount() const
{
    return m_children.size();
}

dae::GameObject *dae::GameObject::GetChildAt(size_t index) const
{
    return m_children.at(index).get();
}

const glm::vec3 &dae::GameObject::GetWorldPosition() const
{
    if (m_positionIsDirty)
    {
        UpdateWorldPosition();
    }

    return m_worldTransform->Position;
}

const dae::Transform &dae::GameObject::GetLocalTransform() const
{
    return *m_localTransform;
}

void dae::GameObject::SetLocalPosition(const glm::vec3 &position)
{
    m_localTransform->Position = position;
    SetPositionDirty();
}

void dae::GameObject::SetLocalScale(float scale)
{
    m_localTransform->Scale = scale;
    SetPositionDirty();
}

void dae::GameObject::AddObserver(IObserver *observer)
{
    m_observers.push_back(observer);
}

void dae::GameObject::RemoveObserver(IObserver *observer)
{
    std::erase(m_observers, observer);
}

void dae::GameObject::NotifyObservers(uint32_t event, ObserverData const * const data) const {
    for (const auto observer: m_observers)
        observer->Notify(event, data);
}

void dae::GameObject::AddChild(std::unique_ptr<GameObject> &&child)
{
    m_children.push_back(std::move(child));
}

std::unique_ptr<dae::GameObject> dae::GameObject::RemoveChild(const GameObject *child)
{
    auto const it{std::ranges::find_if(m_children, [child](const auto &ptr){ return ptr.get() == child; })};
    if (it == m_children.end()) return nullptr;

    std::unique_ptr<GameObject> removed = std::move(*it);
    m_children.erase(it);
    return removed;
}

bool dae::GameObject::IsChild(const GameObject *child) const
{
    return std::ranges::find_if(m_children, [child](const auto &ptr) { return ptr.get() == child; }) != m_children.
           end();
}

void dae::GameObject::UpdateWorldPosition() const
{
    if (m_positionIsDirty)
    {
        if (m_pParent == nullptr)
        {
            m_worldTransform->Position = m_localTransform->Position;
        } else
        {
            m_worldTransform->Position = m_pParent->GetWorldPosition() + m_localTransform->Position;
        }
    }
    m_positionIsDirty = false;
}

void dae::GameObject::SetPositionDirty() const
{
    m_positionIsDirty = true;

    for (const auto &child: m_children)
    {
        child->SetPositionDirty();
    }
}
