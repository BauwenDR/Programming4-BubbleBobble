#ifndef MINIGIN_COLLIDERCOMPONENT_HPP
#define MINIGIN_COLLIDERCOMPONENT_HPP

#include "GameComponent.hpp"
#include "GameObject.hpp"

namespace dae
{
    class ColliderData final : public ObserverData
    {
    public:
        ColliderComponent const *collider{};
        glm::vec2 const collisionNormal{};

        explicit ColliderData(ColliderComponent const *const collider, glm::vec2 const &normal) : ObserverData(),
            collider(collider), collisionNormal(normal)
        {
        }
        ~ColliderData() override = default;
    };

    class ColliderComponent : public GameComponent
    {
    public:
        void OnCollisionEnter(ColliderComponent const *collider, glm::vec2 const &normal) const;

        void OnCollisionStay(ColliderComponent const *collider, glm::vec2 const &normal) const;

        void OnCollisionExit(ColliderComponent const *collider) const;

        void Start() override;
        void Update() override;
        void Render() const override{}

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

        ~ColliderComponent() override;

    private:
        glm::vec4 m_collider{};
        glm::vec2 m_center{};

        uint32_t m_tag{};

        void RecalculateCollider();
    };
}

#endif //MINIGIN_COLLIDERCOMPONENT_HPP
