#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class EnemyComponent final : public BaseComponent
	{
	public:
		EnemyComponent();

		virtual ~EnemyComponent() = default;
		EnemyComponent(const EnemyComponent& other) = delete;
		EnemyComponent(EnemyComponent&& other) noexcept = delete;
		EnemyComponent& operator=(const EnemyComponent& other) = delete;
		EnemyComponent& operator=(EnemyComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

	private:
		static const std::string m_ComponentName;
	};

}
