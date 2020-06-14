#include "Pickup.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Scene.h"
#include "BubbleBobbleScene.h"
#include "SceneManager.h"
#include "PlayerComponent.h"
#include "GridComponent.h"
#include "AudioManager.h"

dae::Pickup::Pickup(const std::string& name, const int& points)
	:m_Name(name), m_Points(points)
{
}

dae::Pickup::~Pickup()
{

}

void dae::Pickup::Initialize()
{
	GetTransform()->SetScale(2.f);
	SpriteComponent* sprite = new SpriteComponent("Items/" + m_Name + ".png", 18, 18);
	sprite->AddSpriteAnimation(new SpriteAnimation(1U, 1), "Begin");
	sprite->AddSpriteAnimation(new SpriteAnimation(1U, 2), "End");
	AddComponent(sprite);


	BoxColliderComponent* collider = new BoxColliderComponent(false, true);
	collider->SetTriggerCallBack(std::bind(&Pickup::CallBack, this, std::placeholders::_1, std::placeholders::_2));
	AddComponent(collider);

	RigidBodyComponent* rigid = new RigidBodyComponent(false, 1.f);
	AddComponent(rigid);

	AddComponent(new GridComponent());
}

void dae::Pickup::Update(float elapsed)
{
	if (m_IsPickedUp)
	{
		GetTransform()->TranslateY(25.f * elapsed);

		m_Elapsed += elapsed;
		if (m_Elapsed >= m_ScoreExistanceTime)
		{
			AudioManager::GetService().PlaySFX(1, 10U, 0);
			auto scene = static_cast<BubbleBobbleScene*>(&SCENEMANAGER.GetActiveScene());
			scene->DeductEnemyCount();
			SCENEMANAGER.GetActiveScene().Remove(this);
		}
		
	}
}

void dae::Pickup::Render() const
{
}

void dae::Pickup::CallBack(GameObject* , GameObject* other)
{

	if (other->GetTag() == "Player" && !m_IsPickedUp)
	{
		
		GetComponent<SpriteComponent>()->PlayAnimation("End");
		m_IsPickedUp = true;
		GetComponent<BoxColliderComponent>()->Enable(false);

		other->GetComponent<PlayerComponent>()->AddScore(m_Points);
		m_IsPickedUp = true;
	}
}
