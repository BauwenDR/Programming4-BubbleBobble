#pragma once
#include <algorithm>
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

		void Start() const;
		void Update() const;
		void PostUpdate();
		void Render() const;

		[[nodiscard]] GameObject* GetParent() const;
		void SetParent(GameObject *parent, bool keepWorldPosition);
		[[nodiscard]] size_t GetChildCount() const;
		[[nodiscard]] GameObject* GetChildAt(size_t index) const;

		const glm::vec3& GetWorldPosition();
		void SetLocalPosition(const glm::vec3& position);

		template <GameComponentChild T>
		void AddComponent(std::unique_ptr<T> component)
		{
			if (component == nullptr)
			{
				assert(false && "Cannot add a [null] component");
				return;
			}

			if (&component->GetGameObject() != this)
			{
				assert(false && "Cannot add a child component with a different parent");
				return;
			}

			m_components.push_back(std::move(component));
		}

		template <GameComponentChild T>
		T* GetComponent()
		{

			auto foundComponent{std::find_if(std::begin(m_components), std::end(m_components), [](const auto &component)
			{
				return dynamic_cast<T*>(component.get()) != nullptr;
			})};

			return foundComponent != m_components.end()
				? dynamic_cast<T*>(foundComponent->get())
				: nullptr;
		}

		[[nodiscard]] bool IsMarkedForDelete() const;

		GameObject() = default;
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void AddChild(GameObject* child);
		void RemoveChild(GameObject* child);
		bool IsChild(const GameObject* child) const;

		void UpdateWorldPosition();
		void SetPositionDirty();

		Transform m_localTransform{};
		Transform m_worldTransform{};

		// vec3 for translations if fine for now. Making use of thr Transform in the future is to be considered.
		glm::vec3 m_localPosition{};
		glm::vec3 m_worldPosition{};

		GameObject *m_pParent{};
		std::vector<GameObject*> m_children{};	// TODO: find a way of converting these to unique_ptrs

		std::vector<std::unique_ptr<GameComponent>> m_components{};

		bool m_isToBeRemoved{false};
		bool m_positionIsDirty{false};
	};
}
