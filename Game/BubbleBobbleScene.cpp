#include "BubbleBobbleScene.h"
#include "GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "AudioManager.h"
#include "Devlog.h"
#include <GL\GLU.h>
#include <SDL_opengl.h>
#include "FPSComponent.h"
#include "RigidBodyComponent.h"
#include "GameCommands.h"
#include "StateMachine.h"

dae::BubbleBobbleScene::BubbleBobbleScene() : Scene("BubbleBobbleScene") {}

dae::BubbleBobbleScene::~BubbleBobbleScene() {}

void dae::BubbleBobbleScene::Initialize()
{
	TIME.ScreenFPSCounter(true);

	m_Avatar = new GameObject();
	m_Avatar->AddComponent(new TransformComponent());
	m_Avatar->GetComponent<TransformComponent>()->SetPosition(FVector3(100, 70, 0));
	m_Avatar->GetComponent<TransformComponent>()->SetScale(3.f);
	m_Avatar->AddComponent(new SpriteComponent("../Game/Resources/Character/Bub/Bub.png", 18, 18, 10));
	m_Avatar->GetComponent<SpriteComponent>()->FlipHorizontal();
	m_Avatar->AddComponent(new BoxColliderComponent(false));
	m_Avatar->AddComponent(new RigidBodyComponent(true, 1.f));
	m_Avatar->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(6U, 1), "Idle");
	m_Avatar->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(5U, 2), "Walk");
	m_Avatar->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(5U, 3), "Shoot");
	m_Avatar->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(4U, 4), "Jump");
	m_Avatar->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(6U, 5), "Dead");

	//m_Avatar->GetComponent<BoxColliderComponent>()->SetCollisionCallBack(std::bind(&BubbleBobbleScene::CallBack, this, std::placeholders::_1, std::placeholders::_2));

	Add(m_Avatar);

	m_Box = new GameObject();
	m_Box->AddComponent(new BoxColliderComponent(true));
	m_Box->GetTransform()->SetPosition(0, 0);
	m_Box->GetComponent<BoxColliderComponent>()->SetWidth((float)ENGINE.GetWindowWidth());
	m_Box->GetComponent<BoxColliderComponent>()->SetHeight(50.f);
	
	Add(m_Box);

	//InputManager::GetInstance().SetMaxControllerPlayers(1U);
	InputManager::GetInstance().AssignCommandToButton(XBOXButton::A, new JumpCommand());


}

void dae::BubbleBobbleScene::Update(float elapsed)
{
	auto& input = InputManager::GetInstance();
	const FVector2 leftAxis = input.GetControllerLeftAxis(0U);
	const float speed = 180.f;
	
	if (leftAxis.x != 0 || leftAxis.y != 0)
	{
		m_Avatar->GetComponent<SpriteComponent>()->PlayAnimation("Walk");
		m_Avatar->GetTransform()->TranslateX(leftAxis.x * elapsed * speed);
	}
	else
	{
		m_Avatar->GetComponent<SpriteComponent>()->PlayAnimation("Idle");
	}

	if (leftAxis.x > 0)
	{
		m_Avatar->GetComponent<SpriteComponent>()->FlipHorizontal(true);
	}
	else if (leftAxis.x < 0)
	{
		m_Avatar->GetComponent<SpriteComponent>()->FlipHorizontal(false);
	}

	if (input.IsControllerPressedDown(XBOXButton::A, 0U))
	{
		input.GetCommand(XBOXButton::A)->Execute(m_Avatar);

	}
	if (input.IsControllerPressed(XBOXButton::A, 0U))
	{
		m_Avatar->GetComponent<SpriteComponent>()->PlayAnimation("Dead");
	}

	if (input.IsControllerPressedDown(XBOXButton::RB, 0U))
	{
		
	}

}

void dae::BubbleBobbleScene::Render() const
{

}

