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
#include "PlayerComponent.h"
#include "GridComponent.h"

#include "ObjectPool.h"
#include "ZenChan.h"
#include "Maita.h"
#include "UIComponent.h"
#include "HealthComponent.h"


dae::BubbleBobbleScene::BubbleBobbleScene() 
	: Scene("BubbleBobbleScene")
	, m_Level1("Level/Level_One_Mesh.png", "Level/Level_One_Texture.png")
	, m_Level2("Level/Level_Two_Mesh.png", "Level/Level_Two_Texture.png")
	, m_Level3("Level/Level_Three_Mesh.png", "Level/Level_Three_Texture.png")
{

}

dae::BubbleBobbleScene::~BubbleBobbleScene() {}

void dae::BubbleBobbleScene::Initialize()
{
	m_Level1.Load(this, FPoint2{ 0,0 });
	m_Level2.Load(this, FPoint2{ FPoint2{ 0, float(-ENGINE.GetWindowHeight()) } });
	m_Level3.Load(this, FPoint2{ 0, -ENGINE.GetWindowHeight() * 2.f });

	auto m_UI = new GameObject();
	auto uiComp = new UIComponent(this);
	m_UI->AddComponent(uiComp);
	GetActiveCamera()->AddToScreen(m_UI);

	m_Avatar[0] = new GameObject();
	m_Avatar[0]->SetTag("Player");
	m_Avatar[0]->AddComponent(new PlayerComponent(uiComp));
	m_Avatar[0]->GetComponent<TransformComponent>()->SetPosition(FVector3(70, 70, 0));
	m_Avatar[0]->GetComponent<TransformComponent>()->SetScale(2.f);
	m_Avatar[0]->AddComponent(new HealthComponent());
	m_Avatar[0]->AddComponent(new SpriteComponent("Character/Bub/Bub.png", 18, 18, 15));
	m_Avatar[0]->GetComponent<SpriteComponent>()->FlipHorizontal();
	m_Avatar[0]->AddComponent(new BoxColliderComponent(false));
	m_Avatar[0]->AddComponent(new RigidBodyComponent(true, 1.f));
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(4U, 1), "Idle");
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(3U, 2), "Walk");
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 3), "Shoot");
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 4), "JumpUp");
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 5), "JumpDown");
	m_Avatar[0]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(6U, 6), "Dead");
	m_Avatar[0]->AddComponent(new GridComponent());

	m_Avatar[1] = new GameObject();
	m_Avatar[1]->SetTag("Player");
	m_Avatar[1]->AddComponent(new HealthComponent());
	m_Avatar[1]->AddComponent(new PlayerComponent(uiComp, 10.0f, 15.0f, 1U));
	m_Avatar[1]->GetComponent<TransformComponent>()->SetPosition(FVector3(270, 70, 0));
	m_Avatar[1]->GetComponent<TransformComponent>()->SetScale(2.f);
	m_Avatar[1]->AddComponent(new SpriteComponent("Character/Bob/Bob.png", 18, 18, 15));
	m_Avatar[1]->GetComponent<SpriteComponent>()->FlipHorizontal();
	m_Avatar[1]->AddComponent(new BoxColliderComponent(false));
	m_Avatar[1]->AddComponent(new RigidBodyComponent(true, 1.f));
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(4U, 1), "Idle");
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(3U, 2), "Walk");
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 3), "Shoot");
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 4), "JumpUp");
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(2U, 5), "JumpDown");
	m_Avatar[1]->GetComponent<SpriteComponent>()->AddSpriteAnimation(new SpriteAnimation(6U, 6), "Dead");
	m_Avatar[1]->AddComponent(new GridComponent());

	AddPlayer(m_Avatar[0]);
	AddPlayer(m_Avatar[1]);
	Add(m_Avatar[0]);
	Add(m_Avatar[1]);
	m_PlayerSpawnPoint[0] = m_Avatar[0]->GetTransform()->GetPosition2D();
	m_PlayerSpawnPoint[1] = m_Avatar[1]->GetTransform()->GetPosition2D();

	InputManager::GetInstance().AssignCommandToButton(XBOXButton::A, new JumpCommand());
	InputManager::GetInstance().AssignCommandToButton(XBOXButton::RB, new ShootCommand());

	TIME.AddFPSCounter(*this);

	SpawnLevel1Enemies();
}

void dae::BubbleBobbleScene::Update(float elapsed)
{
	//LEVEL COMPLETED -> MOVE CAMERA DOWN 
	if (m_LevelComleted)
	{
		GetActiveCamera()->Translate(FVector2(0, -m_LevelTransitionSpeed * elapsed));
		if (GetActiveCamera()->GetPosition().y <= float(-ENGINE.GetWindowHeight() * int(m_CurrentLevel)))
		{
			//SPAWN NEXT ENEMIES WHEN ARRIVED
			GetActiveCamera()->SetPosition(FVector2(0, float(-ENGINE.GetWindowHeight() * int( m_CurrentLevel))));
			m_LevelComleted = false;
			m_EnemyCount = 0;
			auto campos = GetActiveCamera()->GetPosition();
			m_PlayerSpawnPoint[0].y += campos.y;
			m_PlayerSpawnPoint[1].y += campos.y;
			if (m_CurrentLevel == 1)
			{
				SpawnLevel2Enemies();
			}
			else if (m_CurrentLevel == 2)
			{
				SpawnLevel3Enemies();
			}

		}
	}

	//CHANGE LEVEL
	if (m_EnemyCount <= 0 && !m_LevelComleted && m_CurrentLevel != 2)
	{
		SetNextLevel();
	}


	//Hide player 2 when its not connected after startscreen
	if (!InputManager::GetInstance().IsControllerConnected(1U))
	{
		m_Avatar[1]->SetActive(false);
	}
}

void dae::BubbleBobbleScene::Render() const
{

}

void dae::BubbleBobbleScene::SetNextLevel()
{
	m_LevelComleted = true;
	m_CurrentLevel++;
	m_PlayerSpawnPoint[0].y -= float(-ENGINE.GetWindowHeight() * int(m_CurrentLevel));
	m_PlayerSpawnPoint[1].y -= float(-ENGINE.GetWindowHeight() * int(m_CurrentLevel));
}

const FPoint2& dae::BubbleBobbleScene::GetSpawnPoint(const uint& id)
{
	return m_PlayerSpawnPoint[id];
}

void dae::BubbleBobbleScene::SpawnLevel1Enemies()
{
	for (auto pos : m_Level1.GetMatiasPositions())
	{
		auto maita = new Maita();
		maita->GetTransform()->SetPosition(pos.x, pos.y, 0);
		m_EnemyCount++;
		Add(maita);
	}

	for (auto pos : m_Level1.GetZenChansPositions())
	{
		auto zen = new ZenChan();
		zen->GetTransform()->SetPosition(pos.x, pos.y, 0);
		m_EnemyCount++;
		Add(zen);
	}
}

void dae::BubbleBobbleScene::SpawnLevel2Enemies()
{
	for (auto pos : m_Level2.GetMatiasPositions())
	{
		auto maita = new Maita();
		maita->SetLinkedScene(this);
		maita->RootInitialize();
		maita->GetTransform()->SetPosition(pos.x, pos.y, 0);
		Add(maita);
		m_EnemyCount++;
	}

	for (auto pos : m_Level2.GetZenChansPositions())
	{
		auto zen = new ZenChan();
		zen->SetLinkedScene(this);
		zen->RootInitialize();
		auto campos = GetActiveCamera()->GetPosition();
		zen->GetTransform()->SetPosition(campos.x + pos.x, campos.y + pos.y, 0);
		Add(zen);
		m_EnemyCount++;
	}
}

void dae::BubbleBobbleScene::SpawnLevel3Enemies()
{
	for (auto pos : m_Level3.GetMatiasPositions())
	{
		auto maita = new Maita();
		maita->SetLinkedScene(this);
		maita->RootInitialize();
		maita->GetTransform()->SetPosition(pos.x, pos.y, 0);
		Add(maita);
		m_EnemyCount++;
	}

	for (auto pos : m_Level3.GetZenChansPositions())
	{
		auto zen = new ZenChan();
		zen->SetLinkedScene(this);
		zen->RootInitialize();
		auto campos = GetActiveCamera()->GetPosition();
		zen->GetTransform()->SetPosition(campos.x + pos.x, campos.y + pos.y, 0);
		Add(zen);
		m_EnemyCount++;
	}
}

