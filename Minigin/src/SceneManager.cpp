#include "SceneManager.hpp"

#include <fstream>

#include <nlohmann/json.hpp>

#include "Render/ResourceManager.hpp"
#include "Scene.hpp"

void dae::SceneManager::Update() const {
	for(const auto& scene : m_scenes)
	{
		scene->Update();
	}

	for (const auto& scene : m_scenes)
	{
		scene->PostUpdate();
	}
}

void dae::SceneManager::Render() const
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

dae::Scene & dae::SceneManager::CreateScene(std::string const & stageName,
	const std::function<std::unique_ptr<GameObject>(nlohmann::json const &)> &prefabGenerator)
{
	using json = nlohmann::json;
	m_scenes.emplace_back(new Scene());
	Scene& scene = *m_scenes.back();

	// TODO log the fact that it failed
	// Return empty scene if json failed to load
	std::ifstream jsonFile{ResourceManager::GetInstance().LoadFile(stageName + ".json")};
	if (!jsonFile.is_open()) return scene;

	for (const json &sceneJson{json::parse(jsonFile)}; const auto &item : sceneJson["prefabs"])
	{
		scene.Add(prefabGenerator(item));
	}

	return scene;
}
