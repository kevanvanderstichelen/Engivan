#include "MiniginPCH.h"
#include "HealthComponent.h"

//REQUIRED: Collider Component in GameObject
dae::HealthComponent::HealthComponent()
	: m_IsDead(false), m_MaxHealth(10), m_CurrentHealth(10) {}

//REQUIRED: Collider Component in GameObject
dae::HealthComponent::HealthComponent(const int& startHealth, const int& maxHealth)
	: m_IsDead(false), m_MaxHealth(maxHealth), m_CurrentHealth(startHealth) {}

void dae::HealthComponent::Initialize()
{
	m_BoxCollider = m_pGameObject->GetComponent<BoxColliderComponent>();

	if (!m_BoxCollider)
	{
		DEBUGLOG.PrintWarning("HealthComponent::Initialize() - No box collider in GameObject! Please assign collider component to GameObject.");
		return;
	}

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
