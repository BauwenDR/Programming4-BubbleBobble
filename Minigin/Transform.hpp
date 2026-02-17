#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		Transform() = default;
		explicit Transform(const glm::vec3 &position) : m_position{ position } {}
		Transform(const float x, const float y, const float z = 0) : m_position{ glm::vec3(x, y, z) } {}

		[[nodiscard]] const glm::vec3& GetPosition() const { return m_position; }
		void SetPosition(float x, float y, float z = 0);
		void SetPosition(const glm::vec3& position);

	private:
		glm::vec3 m_position{};
	};
}
