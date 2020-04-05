#include "BubbleBobbleScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AudioManager.h"
#include "Devlog.h"
#include <GL\GLU.h>
#include <SDL_opengl.h>

dae::BubbleBobbleScene::BubbleBobbleScene()
	:Scene(typeid(BubbleBobbleScene).name())
{
}

dae::BubbleBobbleScene::~BubbleBobbleScene()
{

}

void dae::BubbleBobbleScene::Initialize()
{
	m_pAudioService = new LoggedAudio();
	AudioManager::Provide(m_pAudioService);
	m_pAudioService->AddMusic("../Game/Resources/Audio/Music/BubbleBobble_Main.mp3", 0);
	//m_pAudioService->PlayMusic(0, true);
	Devlog::GetInstance().Print("Move left joystick to move avatar");

	GameObject* startScreen = new GameObject();
	startScreen->AddComponent(new TransformComponent());
	startScreen->AddComponent(new SpriteComponent());
	startScreen->GetComponent<SpriteComponent>()->SetTexture("../Game/Resources/Theme/BubbleBobble_StartScreen.png");
	Add(startScreen);

	m_Avatar = new GameObject();
	m_Avatar->AddComponent(new TransformComponent());
	m_Avatar->GetComponent<TransformComponent>()->SetPosition(FVector3(0, 0, 0));
	m_Avatar->GetComponent<TransformComponent>()->SetScale(3.f);
	m_Avatar->AddComponent(new SpriteComponent());
	m_Avatar->GetComponent<SpriteComponent>()->SetTexture("../Game/Resources/Character/AvatarTemp.png");
	Add(m_Avatar);

	InputManager::GetInstance().SetMaxControllerPlayers(2U);
}

void dae::BubbleBobbleScene::Update(float elapsed)
{
	auto& input = InputManager::GetInstance();
	const FVector2 leftAxis = input.GetControllerLeftAxis(0U);
	const float speed = 40.f;

	if (leftAxis.x != 0 || leftAxis.y != 0)
	{
		m_Avatar->GetTransformComponent()->Translate(FVector2(leftAxis.x * elapsed * speed, leftAxis.y * elapsed * speed));
	}

}

void dae::BubbleBobbleScene::Render() const
{
}
