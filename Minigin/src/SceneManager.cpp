#include "SceneManager.hpp"

#include "Scene.hpp"
#include "Event/Sdbm.hpp"

void dae::SceneManager::Update() {
	if (m_newScene.scene)
	{
		SwitchScenes();
	}

	if(m_activeScene)
	{
		m_activeScene->Update();
		m_activeScene->PostUpdate();
	}
}

void dae::SceneManager::Render() const
{
	if (m_activeScene)
	{
		m_activeScene->Render();
	}
}

void dae::SceneManager::RenderGui() const
{
	if (m_activeScene)
	{
		m_activeScene->RenderGui();
	}
}

void dae::SceneManager::Destroy()
{
	m_activeScene.reset();
	m_newScene.scene.reset();
}

dae::Scene* dae::SceneManager::GetActive() const
{
	return m_activeScene.get();
}

void dae::SceneManager::SwitchScenes()
{
	if (m_activeScene && m_newScene.preserveKeepAlive)
	{
		auto const oldLength{static_cast<ssize_t>(m_newScene.scene->m_objects.size())};
		m_activeScene->TransferKeepAliveObjects(*m_newScene.scene);
		std::for_each(std::begin(m_newScene.scene->m_objects) + oldLength, std::end(m_newScene.scene->m_objects), [](const auto &object)
		{
			object->NotifyObservers(sdbm_hash("scene_manager_scene_switch"), {});
		});
	}

	m_activeScene = std::move(m_newScene.scene);
	m_newScene.scene = nullptr;
}

dae::Scene& dae::SceneManager::CreateScene(bool preserveKeepAlive)
{
	m_newScene = NewScene {
		std::unique_ptr<Scene>(new Scene()), // make_unique cannot be used as default constructor is private (and we can access it because we are a friend)
		preserveKeepAlive
	};

	return *m_newScene.scene;
}
