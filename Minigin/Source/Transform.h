#pragma once
#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

namespace dae
{
	class Transform final
	{
	public:
		Transform();
		Transform(glm::vec3 position);
		Transform(glm::vec3 position, float scale);
		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(float x, float y, float z);
		void SetScale(float scale);
		void SetRotation(float rotation);

	private:
		glm::vec3 m_Position;
		float m_Scale;
		float m_Rotation;
	};
}
