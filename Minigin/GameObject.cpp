#include "GameObject.hpp"

#include "GameComponent.hpp"
#include "ResourceManager.hpp"

bool dae::GameObject::IsMarkedForDelete() const
{
	return m_isToBeRemoved;
}

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start() const
{
	for (const auto &component: m_components)
	{
		component->Start();
	}
}

void dae::GameObject::Update() const
{
	for (const auto &component: m_components)
	{
		component->Update();
	}
}

void dae::GameObject::PostUpdate()
{
	std::erase_if(m_components, [](const auto &component)
	{
		return component->IsMarkedForDelete();
	});
}

void dae::GameObject::Render() const
{
	for (const auto &component: m_components)
	{
		component->Render();
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
		}
		m_positionIsDirty = true;
	}

	if (m_pParent)
	{
		m_pParent->RemoveChild(this);
	}
	m_pParent = parent;
	if (m_pParent != nullptr)
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
	return m_children.at(index);
}

const glm::vec3 &dae::GameObject::GetWorldPosition()
{
	if (m_positionIsDirty)
	{
		UpdateWorldPosition();
	}

	return m_worldPosition;
}

void dae::GameObject::SetLocalPosition(const glm::vec3 &position)
{
	m_localPosition = position;
	m_positionIsDirty = true;
}

void dae::GameObject::AddChild(GameObject *child)
{
	m_children.push_back(child);
}

void dae::GameObject::RemoveChild(GameObject *child)
{
	std::erase(m_children, child);
}

bool dae::GameObject::IsChild(const GameObject *child) const
{
	return std::ranges::find(m_children, child) != m_children.end();
}

void dae::GameObject::UpdateWorldPosition()
{
	if (m_positionIsDirty)
	{
		if (m_pParent == nullptr)
		{
			m_worldPosition = m_localPosition;
		} else
		{
			m_worldPosition = m_pParent->GetWorldPosition() + m_localPosition;
		}
	}
	m_positionIsDirty = false;
}
