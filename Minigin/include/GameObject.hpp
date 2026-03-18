#pragma once
#include <algorithm>
#include <memory>

#include "GameComponent.hpp"
#include "IObserver.hpp"
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

		[[nodiscard]] const Transform &GetLocalTransform() const;
		void SetLocalPosition(const glm::vec3& transform);

		void AddObserver(IObserver* observer);
		void RemoveObserver(IObserver* observer);
		void NotifyObservers(uint32_t event);

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

		void MarkForDelete();
		[[nodiscard]] bool IsMarkedForDelete() const;

		GameObject();
		~GameObject() = default;

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		void AddChild(GameObject *child);
		void RemoveChild(const GameObject *child);
		bool IsChild(const GameObject* child) const;

		void UpdateWorldPosition();
		void SetPositionDirty();

		std::vector<std::unique_ptr<GameObject>> m_children{};	// TODO: find a clean way of converting these to unique_ptrs
		std::vector<std::unique_ptr<GameComponent>> m_components{};

		std::vector<IObserver*> m_observers{};

		std::unique_ptr<Transform> m_localTransform{};
		std::unique_ptr<Transform> m_worldTransform{};

		GameObject *m_pParent{};

		bool m_markedForDelete{false};
		bool m_positionIsDirty{false};
	};
}
