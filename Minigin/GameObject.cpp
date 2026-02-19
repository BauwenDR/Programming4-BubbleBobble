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
	for (const auto &component : m_components)
	{
		component->Start();
	}
}

void dae::GameObject::Update() const
{
	for (const auto &component : m_components)
	{
		component->Update();
	}
}

void dae::GameObject::PostUpdate()
{
	std::erase_if(m_components, [](const auto& component)
	{
		return component->IsMarkedForDelete();
	});
}

void dae::GameObject::Render() const
{
	for (const auto &component : m_components)
	{
		component->Render();
	}
}
