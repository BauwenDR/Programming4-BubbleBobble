#ifndef MINIGIN_ROTATEAROUNDPARENTCOMPONENT_HPP
#define MINIGIN_ROTATEAROUNDPARENTCOMPONENT_HPP

#include "GameComponent.hpp"

namespace demo
{
    class RotateAroundParentComponent : public dae::GameComponent
    {
    public:
        void Start() override {};
        void Update() override;
        void Render() const override {};

        explicit RotateAroundParentComponent(dae::GameObject* owner, const float rotateSpeed, const float radius) : GameComponent(owner), m_rotateSpeed(rotateSpeed), m_rotateRadius(radius) {};
        ~RotateAroundParentComponent() override = default;

    private:
        const float m_rotateSpeed{};
        const float m_rotateRadius{};

        float m_currentAngle{0.0f};
    };
}

#endif //MINIGIN_ROTATEAROUNDPARENTCOMPONENT_HPP