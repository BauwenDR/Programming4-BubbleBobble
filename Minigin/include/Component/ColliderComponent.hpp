#ifndef MINIGIN_COLLIDERCOMPONENT_HPP
#define MINIGIN_COLLIDERCOMPONENT_HPP

#include "GameComponent.hpp"
#include "GameObject.hpp"

namespace dae
{
    class ColliderComponent : public GameComponent
    {
    public:
        void OnCollisionEnter(ColliderComponent const *collider, glm::vec2 const &collisionNormal, glm::vec2 const &normal) const;

        void OnCollisionStay(ColliderComponent const *collider, glm::vec2 const &collisionNormal, glm::vec2 const &normal) const;

        void OnCollisionExit(ColliderComponent const *collider) const;

        void Start() override;
        void Update() override;
        void OnDelete() override;

        void RecalculateCollider();

        [[nodiscard]] glm::vec4 const &GetColliderPosition() const
        {
            return m_collider;
        }

        [[nodiscard]] glm::vec2 const &GetColliderCenter() const
        {
            return m_center;
        }

        [[nodiscard]] uint32_t GetTag() const
        {
            return m_tag;
        };

        ColliderComponent(GameObject &owner, glm::vec2 const &colliderSize, uint32_t tag);

    private:
        glm::vec4 m_collider{};
        glm::vec2 m_center{};

        uint32_t m_tag{};

    };

    class ColliderData final : public ObserverData
    {
    public:
        ColliderComponent const *collider{};
        glm::vec2 const collisionNormal{};
        glm::vec2 const normal{};

        explicit ColliderData(ColliderComponent const *const collider, glm::vec2 const &collisionNormal, glm::vec2 const &normal) : ObserverData(),
            collider(collider), collisionNormal(collisionNormal), normal(normal)
        {
        }
        ~ColliderData() override = default;
    };
}

#endif //MINIGIN_COLLIDERCOMPONENT_HPP
