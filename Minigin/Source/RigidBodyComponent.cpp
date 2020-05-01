#include "MiniginPCH.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"

dae::RigidBodyComponent::RigidBodyComponent(const bool useGravity, const float mass, const float gravity)
	:m_UseGravity(useGravity), m_Mass(mass), m_Gravity(gravity / 10.f)
	,m_Force(0, m_Mass * m_Gravity), m_Acceleration(0,0), m_LinearVelocity(0,0),m_Direction(0,0), m_Velocity(0,0)
{
}

void dae::RigidBodyComponent::Initialize()
{
	if (!m_pGameObject->GetComponent<BoxColliderComponent>())
	{
		DEBUGLOG.PrintError("RigidBodyComponent::RigidBodyComponent() has no Collider component!");
		return;
	}

	EnableGravity(m_UseGravity);

}

void dae::RigidBodyComponent::Update(float elapsed)
{
	m_Acceleration = m_Force / m_Mass;
	m_LinearVelocity += m_Acceleration * elapsed;
	m_LinearVelocity += m_Velocity * elapsed;

	m_pGameObject->GetTransform()->Translate(m_LinearVelocity);
	if (m_UseGravity) m_Force.y = m_Mass * m_Gravity;

	if (m_Velocity.y > 0.f)
	{
		m_Velocity.y -= m_LinearVelocity.y;
	}

}

void dae::RigidBodyComponent::Render()
{
}

const std::string dae::RigidBodyComponent::GetComponentName() const
{
	return std::string();
}

void dae::RigidBodyComponent::EnableGravity(const bool enable)
{
	m_UseGravity = enable;
	m_Force.y = m_UseGravity ? m_Gravity : 0.f;

}

void dae::RigidBodyComponent::AddForce(const float x, const float y)
{
	m_Force.x += x;
	m_Force.y += y + m_Mass * m_Gravity;
}

void dae::RigidBodyComponent::AddForce(const FVector2& force)
{
	AddForce(force.x, force.y);
}

void dae::RigidBodyComponent::SetForce(const float x, const float y)
{
	m_Force.x = x;
	m_Force.y = y + m_Mass * m_Gravity;
}

void dae::RigidBodyComponent::SetForce(const FVector2& force)
{
	SetForce(force.x, force.y);
}

void dae::RigidBodyComponent::AddVelocity(const FVector2& velocity)
{
	m_Velocity += velocity;
}
