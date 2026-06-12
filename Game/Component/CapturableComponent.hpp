#ifndef MINIGIN_CAPTURABLECOMPONENT_HPP
#define MINIGIN_CAPTURABLECOMPONENT_HPP
#include <glm/vec2.hpp>

#include "Component/GameComponent.hpp"

namespace game
{
    class CapturableComponent final : public dae::GameComponent
    {
    public:
        void Update() override;

        void OnCapture() const;
        void OnRelease() const;
        void OnPop(bool flyLeft, int32_t popNumber) const;

        explicit CapturableComponent(dae::GameObject &owner, glm::vec2 poppedSpriteOffset, bool isEnemy);

    private:
        glm::vec2 m_poppedEnemySpriteOffset{};
        bool m_isEnemy{};
    };
}

#endif //MINIGIN_CAPTURABLECOMPONENT_HPP
