#pragma once
#include <vector>
#include <memory>

#include "Scene.hpp"
#include "Singleton.hpp"

namespace dae
{
	struct NewScene
	{
		std::unique_ptr<Scene> scene{};
		bool preserveKeepAlive{};
	};

	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		Scene& CreateScene(bool preserveKeepAlive = true);

		void Update();
		void Render() const;

		void RenderGui() const;

		void Destroy();

	private:
		friend class Singleton;

		std::unique_ptr<Scene> m_activeScene{};
		NewScene m_newScene{};

		void SwitchScenes();
		SceneManager() = default;
	};
}
