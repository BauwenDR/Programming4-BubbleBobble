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
        ColliderComponent const *const collider;

        explicit ColliderData(ColliderComponent const *const collider) : ObserverData(), collider(collider)
        {
        }
    };

    class ColliderComponent : public GameComponent
    {
    public:
        void OnCollisionEnter(ColliderComponent const * collider) const;

        void OnCollisionStay(ColliderComponent const * collider) const;

        void OnCollisionExit(ColliderComponent const * collider) const;

        bool Intersects(const ColliderComponent & colliderComponent) const;

        void Start() override {};
        void Update() override;
        void Render() const override {};

        ColliderComponent(GameObject &owner, const glm::vec4 collider)
            : GameComponent(owner)
              , m_collider(collider)
        {
        }

        ~ColliderComponent() override = default;

    private:
        glm::vec4 m_collider{};
    };
}

#endif //MINIGIN_COLLIDERCOMPONENT_HPP
