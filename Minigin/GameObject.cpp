#include "GameObject.hpp"

#include <ranges>

#include "GameComponent.hpp"
#include "ResourceManager.hpp"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (const auto &component: m_components | std::views::values)
	{
		component->Start(*this);
	}
}

void dae::GameObject::Update()
{
	for (const auto &component: m_components | std::views::values)
	{
		component->Update(*this);
	}
}

void dae::GameObject::Render() const
{
	for (const auto &component: m_components | std::views::values)
	{
		component->Render(*this);
	}
}

void dae::GameObject::OnEndOfFrame()
{
	for (const auto& name : m_components_to_remove)
	{
		m_components.erase(name);
	}

	m_components_to_remove.clear();
}
