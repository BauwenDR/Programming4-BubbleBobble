#include "GameObject.hpp"

#include <ranges>

#include "GameComponent.hpp"
#include "ResourceManager.hpp"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (const auto &component: m_components | std::views::values)
	{
		component->update(*this);
	}
}

void dae::GameObject::Render() const
{
	for (const auto &component: m_components | std::views::values)
	{
		component->render(*this);
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<GameComponent> component)
{
}

void dae::GameObject::AddComponent(std::shared_ptr<GameComponent> component)
{
	m_components.insert(std::make_pair());
}
