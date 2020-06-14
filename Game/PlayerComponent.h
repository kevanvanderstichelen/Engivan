#pragma once
#include "BaseComponent.h"
#include <string>
#include "StateMachine.h"
#include "Projectile.h"
namespace dae
{
	class UIComponent;
	class BubbleBobbleScene;
	class PlayerComponent final : public BaseComponent
	{
	public:
		PlayerComponent(UIComponent* ui, const float moveSpeed = 10.f, const float jumpSpeed = 15.f, const uint id = 0);

		virtual ~PlayerComponent() = default;
		PlayerComponent(const PlayerComponent& other) = delete;
		PlayerComponent(PlayerComponent&& other) noexcept = delete;
		PlayerComponent& operator=(const PlayerComponent& other) = delete;
		PlayerComponent& operator=(PlayerComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		const FVector2& GetMoveAxis() { return m_MoveAxis; }
		const uint& GetID() const { return m_ID; }

		void AddScore(const int& score);

		void DeductLife() { m_CurrentLives--; }
		const int& GetCurrentLives() { return m_CurrentLives; }

	private:
		static const std::string m_ComponentName;
		const float m_MoveSpeed, m_JumpSpeed;
		StateMachine m_FSM;
		FVector2 m_MoveAxis;
		const int m_MaxLives;
		int m_CurrentLives;
		uint m_ID;
		int m_CurrentScore;
		UIComponent* m_UI;

	};


}
