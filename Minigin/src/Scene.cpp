#include <algorithm>
#include "Scene.hpp"

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");

	object->Start();
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(const GameObject &object)
{
	std::erase_if(
		m_objects,
		[&object](const auto &ptr) { return ptr.get() == &object; }
	);
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::AddGui(std::unique_ptr<GuiWindow> gui)
{
	assert(gui != nullptr && "Cannot add a null gui to the scene.");

	m_guis.emplace_back(std::move(gui));
}

void Scene::RemoveGui(const GuiWindow &gui)
{
	std::erase_if(
		m_guis,
		[&gui](const auto &ptr) { return ptr.get() == &gui; }
	);
}

void Scene::RemoveAllGui()
{
	m_guis.clear();
}

void Scene::Update()
{
	for (auto const &object: m_objects)
	{
		object->Update();
	}
}

void Scene::PostUpdate()
{
	for (const auto &gameObject: m_objects)
	{
		gameObject->PostUpdate();
	}

	std::erase_if(m_objects, [](const auto &gameObject)
	{
		return gameObject->IsMarkedForDelete();
	});
}

void Scene::Render() const
{
	for (const auto &object: m_objects)
	{
		object->Render();
	}
}

void Scene::RenderGui() const
{
	for (const auto &gui: m_guis)
	{
		gui->DrawWindow();
	}
}
