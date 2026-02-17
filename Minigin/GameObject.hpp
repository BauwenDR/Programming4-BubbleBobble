#pragma once
#include <iostream>
#include <string>
#include <memory>

#include "GameComponent.hpp"
#include "Transform.hpp"

template <typename T>
concept GameComponentChild = std::is_base_of_v<dae::GameComponent, T>;

namespace dae
{

	class Texture2D;
	class GameObject final
	{
	public:
		Transform Position{};

		void Start();
		void Update();
		void Render() const;


		template <GameComponentChild T>
		void AddComponent(const std::shared_ptr<T>& component)
		{
			// TODO better error handling
			const auto &[_, success]{m_components.try_emplace(typeid(T).name(), component)};

			if (!success)
			{
				std::cerr << "Failed to add component " << typeid(component).name() << std::endl;
			}
		}

		template <GameComponentChild T>
		std::shared_ptr<T> GetComponent()
		{
			if (const auto it = m_components.find(typeid(T).name()); it != m_components.end())
			{
				return std::dynamic_pointer_cast<T>(it->second);
			}

			return std::shared_ptr<T>(nullptr);
		}

		template <GameComponentChild T>
		void RemoveComponent()
		{
			m_components.erase(typeid(T).name());
		}

		GameObject() = default;
		~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::unordered_map<std::string, std::shared_ptr<GameComponent>> m_components{};
	};
}
