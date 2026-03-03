#include "RotateAroundParentComponent.hpp"

#include "GameObject.hpp"
#include "Time.hpp"

#include <numbers>

namespace demo
{
    void RotateAroundParentComponent::Update()
    {
        constexpr float pi2{2.0f * std::numbers::pi_v<float>};

        // Rotate and then make sure angle is between 0 and 2pi
        m_currentAngle += m_rotateSpeed * Time::get_delta_time();
        m_currentAngle = std::fmodf(m_currentAngle, pi2);

        GetGameObject().SetLocalPosition(glm::vec3
        {
            cosf(m_currentAngle) * m_rotateRadius,
            sinf(m_currentAngle) * m_rotateRadius,
            0.0f
        });
    }
}
