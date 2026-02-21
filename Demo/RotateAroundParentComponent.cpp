#include "RotateAroundParentComponent.hpp"

#include "GameObject.hpp"
#include "Time.hpp"

namespace demo
{
    void RotateAroundParentComponent::Update()
    {
        //constexpr float pi2{std::numbers::pi * 2.0f};

        // Rotate and then make sure angle is between 0 and 2pi
        m_currentAngle += m_rotateSpeed * Time::get_delta_time();
        //m_currentAngle = fmod(m_currentAngle + fmod(m_currentAngle, pi2), pi2);

        GetGameObject()->SetLocalPosition(glm::vec3
        {
            cosf(m_currentAngle) * m_rotateRadius,
            sinf(m_currentAngle) * m_rotateRadius,
            0.0f
        });
    }
}
