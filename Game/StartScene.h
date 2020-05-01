#pragma once
#include "Scene.h"
namespace dae
{
	class LoggedAudio;
	class StartScene final : public Scene
	{
	public:
		StartScene();
		~StartScene();

		StartScene(const StartScene& other) = delete;
		StartScene(StartScene&& other) noexcept = delete;
		StartScene& operator=(const StartScene& other) = delete;
		StartScene& operator=(StartScene&& other) noexcept = delete;

		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;

	private:
		LoggedAudio* m_pAudioService = nullptr;
		GameObject* m_pBackground = nullptr;
		GameObject* m_pMenuText = nullptr;
		GameObject* m_pPlayerText = nullptr;
		GameObject* m_pBonus1Text = nullptr;
		GameObject* m_pBonus2Text = nullptr;
		GameObject* m_pMysteryText = nullptr;
		GameObject* m_ConnectedText = nullptr;
		GameObject* m_StartText = nullptr;
		GameObject* m_UI = nullptr;
		GameObject* m_StartLogo = nullptr;
		int m_ButtonACounter = 0;
	};

}
