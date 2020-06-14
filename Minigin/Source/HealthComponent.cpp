#include "MiniginPCH.h"
#include "HealthComponent.h"

//REQUIRED: Collider Component in GameObject
dae::HealthComponent::HealthComponent()
	: m_MaxHealth(1), m_CurrentHealth(1) {}

//REQUIRED: Collider Component in GameObject
dae::HealthComponent::HealthComponent(const int& startHealth, const int& maxHealth)
	: m_MaxHealth(maxHealth), m_CurrentHealth(startHealth) {}

void dae::HealthComponent::Initialize()
{
	m_CurrentHealth = m_MaxHealth;
}

void dae::HealthComponent::Update(float)
{
}

void dae::HealthComponent::Render()
{
}

const std::string dae::HealthComponent::GetComponentName() const
{
	return std::string();
}
