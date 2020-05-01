#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "Utilities.h"

const std::string dae::TransformComponent::m_ComponentName{ "TransformComponent" };

dae::TransformComponent::TransformComponent()
	:m_Position{ 0,0,0 }, m_Rotation{ 0 }, m_Scale{ 1 }, m_Pivot{ 0,0,0 } {}

dae::TransformComponent::TransformComponent(const FVector3& position)
	: m_Position{ position }, m_Rotation{ 0 }, m_Scale{ 1 } {}

dae::TransformComponent::TransformComponent(const FVector3& position, const float rotation)
	: m_Position{ position }, m_Rotation{ rotation }, m_Scale{ 1 }, m_Pivot{ 0,0,0 } {}

dae::TransformComponent::TransformComponent(const FVector3& position, const float rotation, const float scale)
	: m_Position{ position }, m_Rotation{ rotation }, m_Scale{ scale }, m_Pivot{ 0,0,0 } {}


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

void dae::TransformComponent::SetPosition(const FVector3& position)
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

void dae::TransformComponent::Translate(const float x, const float y)
{

	m_Position.x += x;
	m_Position.y += y;
}				

void dae::TransformComponent::Translate(const FVector2& pos)
{

	m_Position.x += pos.x;
	m_Position.y += pos.y;
}

void dae::TransformComponent::Translate(const float x, const float y, const float )
{

	m_Position.x += x;
	m_Position.y += y;
}

void dae::TransformComponent::Translate(const FVector3& pos)
{


	m_Translate.x += pos.x;
	m_Translate.y += pos.y;
}

void dae::TransformComponent::TranslateX(const float x)
{
	m_Position.x += x;
}

void dae::TransformComponent::TranslateY(const float y)
{
	m_Position.y += y;
}

const std::string dae::TransformComponent::GetComponentName() const
{
	return m_ComponentName;
}

const glm::vec3 dae::TransformComponent::GetPosition() const
{
	return m_Position;
}

const FPoint2 dae::TransformComponent::GetPosition2D() const
{
	return FPoint2(m_Position.x, m_Position.y);
}

const float dae::TransformComponent::GetScale() const
{
	return m_Scale;
}

const float dae::TransformComponent::GetRotation() const
{
	return m_Rotation;
}
