#include "Scene.hpp"

#include <iterator>
#include <algorithm>

using namespace dae;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");

	object->Start();
	m_newObjects.emplace_back(std::move(object));
}

std::unique_ptr<GameObject> Scene::Remove(GameObject const *object)
{
	auto const it{std::ranges::find_if(m_objects, [object](const auto &ptr){ return ptr.get() == object; })};
	if (it == m_objects.end()) return nullptr;

	std::unique_ptr<GameObject> removed = std::move(*it);
	m_objects.erase(it);
	return removed;
}

void Scene::MoveInto(std::unique_ptr<GameObject> object)
{
	assert(object != nullptr && "Cannot add a null GameObject to the scene.");
	m_objects.emplace_back(std::move(object));
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::AddGui(std::unique_ptr<GuiWindow> &&gui)
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

void Scene::Start()
{
	for (auto const &object: m_objects)
	{
		object->Start();
	}

	while (m_newObjects.size() > 0)
	{
		TransferNewObjects();
		for (auto const &object: m_objects)
		{
			object->Start();
		}
	}
}

void Scene::Update() const
{
	for (auto const &object: m_objects)
	{
		object->Update();
	}

	for (auto const &object: m_objects)
	{
		object->LateUpdate();
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

	if (m_newObjects.size() > 0)
	{
		TransferNewObjects();
	}

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

void Scene::TransferNewObjects()
{
	m_objects.insert(m_objects.end(),
			   std::make_move_iterator(m_newObjects.begin()),
			   std::make_move_iterator(m_newObjects.end()));
	m_newObjects.clear();
}

void Scene::TransferKeepAliveObjects(Scene &newScene)
{
	auto middle = std::ranges::stable_partition(m_objects,
		[&](const auto &object)
		{
			return !object->KeepAlive;
		}
	);

	newScene.m_objects.reserve(newScene.m_objects.size() + middle.size());
	std::ranges::move(middle, std::back_inserter(newScene.m_objects));
	m_objects.erase(middle.begin(), middle.end());
}
