#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent();

		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

	private:
		static const std::string m_ComponentName;
	};

}

