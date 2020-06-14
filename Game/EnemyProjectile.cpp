#include "EnemyProjectile.h"
#include "SpriteComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "HealthComponent.h"
#include "TransformComponent.h"

dae::EnemyProjectile::EnemyProjectile(GameObject* shotFrom)
	:m_pLinkedGameObject(shotFrom)
{
}

dae::EnemyProjectile::~EnemyProjectile()
{
}

void dae::EnemyProjectile::Initialize()
{
	SetTag("Projectile");
	GetTransform()->SetScale(2.f);
	SpriteComponent* sprite = new SpriteComponent("Character/Maita/Maita_Projectile.png", 25, 25, 20);
	AddComponent(sprite);
	sprite->AddSpriteAnimation(new SpriteAnimation(4U, 1), "Begin");
	sprite->AddSpriteAnimation(new SpriteAnimation(3U, 2), "End");
	sprite->PlayAnimation("Begin");

	BoxColliderComponent* collider = new BoxColliderComponent(false, true);
	collider->SetTriggerCallBack(std::bind(&EnemyProjectile::CallBack, this, std::placeholders::_1, std::placeholders::_2));
	AddComponent(collider);

}

void dae::EnemyProjectile::Update(float elapsed)
{
	if (!m_IsValid)
	{
		auto sprite = GetComponent<SpriteComponent>();
		if (sprite->IsFullAnimationPlayed())
		{
			GetParent()->RemoveChild(this);
		}
	}
	else
	{
		GetTransform()->Translate(m_Direction * m_Speed * elapsed);
	}

}

void dae::EnemyProjectile::Render() const
{
}

void dae::EnemyProjectile::CallBack(GameObject* , GameObject* other)
{
	if (other->GetTag() == "Enemy" || other->GetTag() == "Projectile" || other->GetTag() == "Ignore") return;

	if (other->GetTag() == "Player")
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
		GetComponent<SpriteComponent>()->PlayFullAnimation("End");
	}

	m_IsValid = false;
}
