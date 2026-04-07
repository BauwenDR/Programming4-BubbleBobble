#pragma once
#include <memory>
#include <vector>

#include "GameObject.hpp"
#include "GuiWindow.hpp"

namespace dae
{
	class Scene final
	{
	public:
		void Add(std::unique_ptr<GameObject> object);
		void Remove(const GameObject& object);
		void RemoveAll();


		void AddGui(std::unique_ptr<GuiWindow> gui);
		void RemoveGui(const GuiWindow &gui);
		void RemoveAllGui();

		void Update();
		void PostUpdate();

		void Render() const;
		void RenderGui() const;

		~Scene() = default;
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

	private:
		friend class SceneManager;
		explicit Scene() = default;

		std::vector <std::unique_ptr<GameObject>> m_objects{};
		std::vector <std::unique_ptr<GuiWindow>> m_guis{};
	};

}
