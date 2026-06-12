#include "SceneManager.hpp"

#include <algorithm>

#include "Scene.hpp"
#include "Event/EventManager.hpp"
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
	EventManager::GetInstance().SendEvent(sdbm_hash("scene_manager_scene_switch"));
	EventManager::GetInstance().TriggerEvents();

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
		m_activeScene->TransferKeepAliveObjects(*m_newScene.scene);
	}

	EventManager::GetInstance().SendEvent(sdbm_hash("scene_manager_scene_switch"));
	EventManager::GetInstance().TriggerEvents();

	m_activeScene = std::move(m_newScene.scene);
	m_activeScene->Start();

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
