#include "MiniginPCH.h"
#include "TransformComponent.h"

const std::string dae::TransformComponent::m_ComponentName{ "TransformComponent" };

dae::TransformComponent::TransformComponent()
	:m_Position{ 0,0,0 }, m_Rotation{ 0 }, m_Scale{ 1 } {}

dae::TransformComponent::TransformComponent(const glm::vec3& position)
	: m_Position{ position }, m_Rotation{ 0 }, m_Scale{ 1 } {}

dae::TransformComponent::TransformComponent(const glm::vec3& position, const float rotation)
	: m_Position{ position }, m_Rotation{ rotation }, m_Scale{ 1 } {}

dae::TransformComponent::TransformComponent(const glm::vec3& position, const float rotation, const float scale)
	: m_Position{ position }, m_Rotation{ rotation }, m_Scale{ scale } {}


void dae::TransformComponent::Initialize()
{

}

void dae::TransformComponent::Update(float)
{
}

void dae::TransformComponent::Render()
{
}

void dae::TransformComponent::SetPosition(const float x, const float y)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = 0;
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}

void dae::TransformComponent::SetPosition(const glm::vec3& position)
{
	m_Position = position;
}

void dae::TransformComponent::SetScale(const float scale)
{
	m_Scale = scale;
}

void dae::TransformComponent::SetRotation(const float rotation)
{
	m_Rotation = rotation;
}

const std::string dae::TransformComponent::GetComponentName() const
{
	return m_ComponentName;
}

const glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

const float dae::TransformComponent::GetScale() const
{
	return m_Scale;
}

const float dae::TransformComponent::GetRotation() const
{
	return m_Rotation;
}
