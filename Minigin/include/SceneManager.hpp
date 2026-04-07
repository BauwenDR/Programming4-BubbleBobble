#pragma once
#include <vector>
#include <memory>
#include "Scene.hpp"
#include "Singleton.hpp"
#include "nlohmann/json.hpp"

namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene();
		Scene& CreateScene(const std::string &stageName, const std::function<std::unique_ptr<GameObject>(nlohmann::json const &)> &prefabGenerator);

		void Update() const;
		void Render() const;

		void RenderGui() const;

		void Destroy();

	private:
		friend class Singleton;

		SceneManager() = default;
		std::vector<std::unique_ptr<Scene>> m_scenes{};
	};
}
