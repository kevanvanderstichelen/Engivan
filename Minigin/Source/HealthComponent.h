#pragma once
#include "BaseComponent.h"
#include <string>
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

		const bool IsDead() const noexcept { return m_IsDead; }

	private:
		static const std::string m_ComponentName;
		bool m_IsDead;
		const int m_MaxHealth;
		int m_CurrentHealth;
		BoxColliderComponent* m_BoxCollider;
	};

}

