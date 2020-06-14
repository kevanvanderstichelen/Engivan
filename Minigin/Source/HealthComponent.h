#pragma once
#include "BaseComponent.h"
#include <string>
#include "GameObject.h"
namespace dae
{
	class HealthComponent final : public BaseComponent
	{
	public:
		HealthComponent();
		HealthComponent(const int& startHealth, const int& maxHealth);

		virtual ~HealthComponent() = default;
		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) noexcept = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		const bool IsDead() const noexcept { return m_CurrentHealth <= 0; }

		void DoDamage() { m_CurrentHealth--; }
		void DoDamage(const int& amount) { m_CurrentHealth -= amount; }

		void SetLinkedObject(GameObject* obj) { m_pDamagedByObject = obj; }
		GameObject* GetLinkedObject() { return m_pDamagedByObject; }

		void Reset() {m_CurrentHealth = m_MaxHealth;}

	private:
		static const std::string m_ComponentName;
		const int m_MaxHealth;
		int m_CurrentHealth;
		BoxColliderComponent* m_BoxCollider;
		GameObject* m_pDamagedByObject = nullptr;
	};

}

