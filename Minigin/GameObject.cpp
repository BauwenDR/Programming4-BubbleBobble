#include "GameObject.hpp"

#include <iostream>
#include <ranges>

#include "GameComponent.hpp"
#include "ResourceManager.hpp"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Start()
{
	for (const auto &component: m_components | std::views::values)
	{
		component->start(*this);
	}
}

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
