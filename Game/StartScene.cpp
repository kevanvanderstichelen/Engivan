#include "StartScene.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AudioManager.h"
#include "InputManager.h"
#include "TextComponent.h"
#include "UIComponent.h"

dae::StartScene::StartScene() : Scene("StartScene") {}

dae::StartScene::~StartScene() {}

void dae::StartScene::Initialize()
{
	//AUDIO
	m_pAudioService = new LoggedAudio();
	AudioManager::Provide(m_pAudioService);
	m_pAudioService->AddMusic("../Game/Resources/Audio/Music/BubbleBobble_Main.mp3", 0);
	m_pAudioService->PlayMusic(0, true);

	//TEXT ON START SCREEN / INFO
	const auto& windowWidth = ENGINE.GetWindowWidth();
	const auto& windowHeight = ENGINE.GetWindowHeight();
	const auto& font18 = ResourceManager::GetInstance().LoadFont("../Game/Resources/Font/BubbleBobbleFont.ttf", 18);
	const auto& font12 = ResourceManager::GetInstance().LoadFont("../Game/Resources/Font/BubbleBobbleFont.ttf", 12);

	m_pMenuText = new GameObject();
	m_pMenuText->AddComponent(new TransformComponent());
	m_pMenuText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 100.f, 0));
	m_pMenuText->AddComponent(new TextComponent("PUSH XBOX BUTTON A TO START", font18, TextAllignment::Middle));
	Add(m_pMenuText);

	m_pPlayerText = new GameObject();
	m_pPlayerText->AddComponent(new TransformComponent());
	m_pPlayerText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 150.f, 0));
	m_pPlayerText->AddComponent(new TextComponent("1 PLAYER GAME, CONNECT GAMEPAD FOR MORE", font12, TextAllignment::Middle));
	Add(m_pPlayerText);

	m_pBonus1Text = new GameObject();
	m_pBonus1Text->AddComponent(new TransformComponent());
	m_pBonus1Text->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 250.f, 0));
	m_pBonus1Text->AddComponent(new TextComponent("1ST BONUS FOR	20000 PTS.", font18, TextAllignment::Middle));
	Add(m_pBonus1Text);

	m_pBonus2Text = new GameObject();
	m_pBonus2Text->AddComponent(new TransformComponent());
	m_pBonus2Text->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 300.f, 0));
	m_pBonus2Text->AddComponent(new TextComponent("2ND BONUS FOR	80000 PTS.", font18, TextAllignment::Middle));
	Add(m_pBonus2Text);

	m_pMysteryText = new GameObject();
	m_pMysteryText->AddComponent(new TransformComponent());
	m_pMysteryText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 350.f, 0));
	m_pMysteryText->AddComponent(new TextComponent("AND MYSTERY !?...", font18, TextAllignment::Middle));
	Add(m_pMysteryText);

	m_ConnectedText = new GameObject();
	m_ConnectedText->AddComponent(new TransformComponent());
	m_ConnectedText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 450.f, 0));
	m_ConnectedText->AddComponent(new TextComponent("CONNECTED CONTROLLERS: ", font12, TextAllignment::Middle));
	Add(m_ConnectedText);

	//THEME BACKGROUND
	m_pBackground = new GameObject();
	m_pBackground->AddComponent(new TransformComponent());
	m_pBackground->GetComponent<TransformComponent>()->SetPosition(FVector3(0,0, 1));
	m_pBackground->AddComponent(new SpriteComponent("../Game/Resources/Theme/BubbleBobble_StartScreen.png"));
	Add(m_pBackground);

	m_StartText = new GameObject();
	m_StartText->AddComponent(new TransformComponent());
	m_StartText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 380.f, 0));
	m_StartText->AddComponent(new TextComponent("PRESS XBOX BUTTON A TO CONTINUE", font12, TextAllignment::Middle));
	Add(m_StartText);

	m_StartLogo = new GameObject();
	m_StartLogo->AddComponent(new TransformComponent());
	m_StartLogo->GetTransform()->SetScale(2.f);
	m_StartLogo->GetTransform()->SetPosition(65.0f, 30.f, 0);
	m_StartLogo->AddComponent(new SpriteComponent("../Game/Resources/Theme/StartLogo.png", 256, 256, 60));
	m_StartLogo->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(6, 1), "Default");
	m_StartLogo->GetComponent<SpriteComponent>()->PlayAnimation("Default");
	Add(m_StartLogo);

	m_UI = new GameObject();
	m_UI->AddComponent(new UIComponent());
	Add(m_UI);

	//INTERACTIONS
	InputManager::GetInstance().SetMaxControllerPlayers(3U);
}

void dae::StartScene::Update(float )
{
	//UPDATE MENU INTERACTION
	auto& input = InputManager::GetInstance();
	if (input.IsControllerPressedDown(XBOXButton::A, 0U))
	{
		Remove(m_pBackground);
		Remove(m_StartText);
		Remove(m_StartLogo);
		m_ButtonACounter++;
		if (m_ButtonACounter >= 2)
		{
			SCENEMANAGER.SetActiveScene("BubbleBobbleScene");
		}
	}

	//UPDATE CONTROLLERS TEXT
	std::string connectedText = "CONNECTED CONTROLLERS: ";
	uint connectedCount = 0U;
	for (uint i{} ; i < input.GetMaxControllerPlayers(); ++i)
	{
		if (input.IsControllerConnected(i))
		{
			connectedText += std::to_string(i + 1) + " ";
			connectedCount++;
		}
	}
	m_ConnectedText->GetComponent<TextComponent>()->SetText(connectedText);
	m_pPlayerText->GetComponent<TextComponent>()->SetText(std::to_string(connectedCount) + " PLAYER GAME, CONNECT GAMEPAD FOR MORE");
}

void dae::StartScene::Render() const
{
}
