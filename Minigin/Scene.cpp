#include <algorithm>
#include "Scene.hpp"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");

	object->Start();
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject& object)
{
	std::erase_if(
		m_objects,
		[&object](const auto& ptr) { return ptr.get() == &object; }
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for(auto const& object : m_objects)
	{
		object->Update();
	}
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		object->Render();
	}
}

void Scene::OnEndOfFrame()
{
	for (const auto& object : m_objects)
	{
		object->OnEndOfFrame();
	}
}

