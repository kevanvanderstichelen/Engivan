#pragma once
#include "BaseComponent.h"
#include "GameObject.h"
#include <string>

namespace dae
{
	class UIComponent final : public BaseComponent
	{
	public:
		UIComponent();

		virtual ~UIComponent() = default;
		UIComponent(const UIComponent& other) = delete;
		UIComponent(UIComponent&& other) noexcept = delete;
		UIComponent& operator=(const UIComponent& other) = delete;
		UIComponent& operator=(UIComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

	private:
		static const std::string m_ComponentName;
		uint m_Player1Score, m_Player2Score, m_TotalScore;
		GameObject* m_pPlayer1Text;
		GameObject* m_pPlayer2Text;
		GameObject* m_pTotalText;
		GameObject* m_pPlayer1ScoreText;
		GameObject* m_pPlayer2ScoreText;
		GameObject* m_pTotalScoreText;
	};

}
