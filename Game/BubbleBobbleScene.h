#pragma once
#include "Scene.h"
#include "Command.h"
#include "InputManager.h"
namespace dae
{
	class LoggedAudio;
	class BubbleBobbleScene final : public Scene
	{
	public:
		BubbleBobbleScene();
		~BubbleBobbleScene();

		BubbleBobbleScene(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene(BubbleBobbleScene&& other) noexcept = delete;
		BubbleBobbleScene& operator=(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene& operator=(BubbleBobbleScene&& other) noexcept = delete;

		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;
	private:
		LoggedAudio* m_pAudioService = nullptr;
		GameObject* m_Avatar;
	};

	class MoveCommand final : public Command
	{
		virtual void Execute() override
		{
			
		};
	};
}


