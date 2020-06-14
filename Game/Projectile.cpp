#include "Projectile.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "SceneManager.h"
#include "HealthComponent.h"
#include "PlayerComponent.h"



dae::Projectile::Projectile(GameObject* shotFrom)
	:m_pLinkedGameObject(shotFrom)
{
}

dae::Projectile::~Projectile()
{
}

void dae::Projectile::Initialize()
{
	SetTag("Projectile");
	GetTransform()->SetScale(2.f);
	uint id = m_pLinkedGameObject->GetComponent<PlayerComponent>()->GetID();

	SpriteComponent* sprite;
	if (id == 0)
	{
		sprite = new SpriteComponent("Items/Bub_Projectile.png", 18, 18, 20);
	}
	else
	{
		sprite = new SpriteComponent("Items/Bob_Projectile.png", 18, 18, 20);
	}

	AddComponent(sprite);
	sprite->AddSpriteAnimation(new SpriteAnimation(6U, 1), "Begin");
	sprite->AddSpriteAnimation(new SpriteAnimation(2U, 2), "End");
	sprite->AddSpriteAnimation(new SpriteAnimation(2U, 3), "Pop");
	sprite->PlayAnimation("Begin");
	
	BoxColliderComponent* collider = new BoxColliderComponent(false, true);
	collider->SetTriggerCallBack(std::bind(&Projectile::CallBack, this, std::placeholders::_1, std::placeholders::_2));
	AddComponent(collider);

	RigidBodyComponent* rigid = new RigidBodyComponent(false, 0.1f, 0.1f);
	AddComponent(rigid);


	
}

void dae::Projectile::Update(float elapsed)
{

	if (!m_IsValid)
	{

		m_EndElapsed += elapsed;

		if (m_EndElapsed >= m_EndExistanceTime - 0.5f)
		{
			GetComponent<SpriteComponent>()->PlayAnimation("Pop");
		}

		if (m_EndElapsed >= m_EndExistanceTime)
		{
			//delete this;
			GetParent()->RemoveChild(this);
		}

	}
	else
	{
		GetTransform()->Translate(m_Direction * m_Speed * elapsed);
	}
}

void dae::Projectile::Render() const
{
}

void dae::Projectile::CallBack(GameObject* , GameObject* other)
{
	if (!m_IsValid) return;
	if (other->GetTag() == "Player" || other->GetTag() == "Projectile" || other->GetTag() == "Ignore") return;

	if (other->GetTag() == "Enemy")
	{
		auto health = other->GetComponent<HealthComponent>();
		if (health)
		{
			health->SetLinkedObject(m_pLinkedGameObject);
			health->DoDamage();
		}
		GetParent()->RemoveChild(this);
	}
	else
	{
		GetComponent<SpriteComponent>()->PlayAnimation("End");
		RigidBodyComponent* rigid = GetComponent<RigidBodyComponent>();
		rigid->EnableGravity(true);
	}

	m_IsValid = false;
}
