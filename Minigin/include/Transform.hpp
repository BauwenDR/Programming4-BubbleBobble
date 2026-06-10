#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class Transform final
	{
	public:
		glm::vec3 Position{};
		float Scale{1.0f};

		Transform() = default;
		explicit Transform(const glm::vec3 &position) : Position{ position } {}
		Transform(const float x, const float y, const float z = 0) : Position{ glm::vec3(x, y, z) } {}
	};
}
