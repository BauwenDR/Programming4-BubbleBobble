#pragma once
#include <string>
#include <memory>

#include "GameComponent.hpp"
#include "Transform.hpp"

template <typename T>
concept IsGameComponent = std::is_base_of_v<GameComponent, T>;

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		Transform Transform{};

		void Update();
		void Render() const;

		void AddComponent(std::shared_ptr<GameComponent> component);

		template <IsGameComponent T>
		std::shared_ptr<T> GetComponent()
		{
			if (const auto it = m_components.find(typeid(T).name()); it != m_components.end())
			{
				return it->second;
			}

			return std::shared_ptr<T>(nullptr);
		}

		template <IsGameComponent T>
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
