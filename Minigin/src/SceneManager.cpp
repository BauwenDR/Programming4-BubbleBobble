#include "SceneManager.hpp"
#include "Scene.hpp"

void dae::SceneManager::Update()
{
	for(auto& scene : m_scenes)
	{
		scene->Update();
	}

	for (const auto& scene : m_scenes)
	{
		scene->PostUpdate();
	}
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_scenes)
	{
		scene->Render();
	}
}

void dae::SceneManager::RenderGui() const
{
	for (const auto& scene : m_scenes)
	{
		scene->RenderGui();
	}
}

void dae::SceneManager::Destroy()
{
	m_scenes.clear();
}

dae::Scene& dae::SceneManager::CreateScene()
{
	m_scenes.emplace_back(new Scene());
	return *m_scenes.back();
}
