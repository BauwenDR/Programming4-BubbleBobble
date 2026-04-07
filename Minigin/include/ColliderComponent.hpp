#ifndef MINIGIN_COLLIDERCOMPONENT_HPP
#define MINIGIN_COLLIDERCOMPONENT_HPP

#include "GameComponent.hpp"
#include "GameObject.hpp"
#include "Sdbm.hpp"

namespace dae
{
    class ColliderData final : public ObserverData
    {
    public:
        ColliderComponent const * collider{};
        glm::vec2 const collisionNormal{};
        float const penetration{};

        explicit ColliderData(ColliderComponent const *const collider, glm::vec2 const & normal) : ObserverData(), collider(collider), collisionNormal(normal)
        {
        }
    };

    class ColliderComponent : public GameComponent
    {
    public:
        void OnCollisionEnter(ColliderComponent const *collider, glm::vec2 const & normal) const;
        void OnCollisionStay(ColliderComponent const *collider, glm::vec2 const & normal) const;
        void OnCollisionExit(ColliderComponent const *collider) const;

        void Start() override;
        void Update() override;
        void Render() const override {};

        glm::vec4 const &GetColliderPosition() const
        {
            return m_collider;
        }

        glm::vec2 const &GetColliderCenter() const
        {
            return m_center;
        }

        ColliderComponent(GameObject &owner, const glm::vec2 colliderSize)
            : GameComponent(owner)
              , m_collider(glm::vec4{0.0f,0.0f,colliderSize.x,colliderSize.y})
        {
        }

        ~ColliderComponent() override = default;

    private:
        glm::vec4 m_collider{};
        glm::vec2 m_center{};
    };
}

#endif //MINIGIN_COLLIDERCOMPONENT_HPP
