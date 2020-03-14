#include "MiniginPCH.h"
#include "Transform.h"

dae::Transform::Transform()
	: m_Position{ 0,0,0 }, m_Scale{ 1 }
{
}

dae::Transform::Transform(glm::vec3 position)
	: m_Position{ position }, m_Scale{ 1 }
{
}

dae::Transform::Transform(glm::vec3 position, float scale)
	: m_Position{ position }, m_Scale{ scale }
{
}

void dae::Transform::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::Transform::SetScale(float scale)
{
	m_Scale = scale;
}

void dae::Transform::SetRotation(float rotation)
{
	m_Rotation = rotation;
}
