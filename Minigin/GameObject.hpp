#pragma once
#include <string>
#include <memory>
#include "Transform.hpp"

class GameComponent;

namespace dae
{
	class Texture2D;
	class GameObject final
	{
	public:
		void Update();
		void Render() const;

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
