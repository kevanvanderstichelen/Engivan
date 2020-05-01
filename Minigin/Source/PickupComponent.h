#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class PickupComponent final : public BaseComponent
	{
	public:
		PickupComponent();

		virtual ~PickupComponent() = default;
		PickupComponent(const PickupComponent& other) = delete;
		PickupComponent(PickupComponent&& other) noexcept = delete;
		PickupComponent& operator=(const PickupComponent& other) = delete;
		PickupComponent& operator=(PickupComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

	private:
		static const std::string m_ComponentName;
	};

}
