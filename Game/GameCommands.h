#pragma once
#include "Command.h"
#include "PlayerComponent.h"
#include "AudioManager.h"
namespace dae
{
	class ShootCommand final : public Command
	{
		virtual void Execute(GameObject* avatar) override
		{
			auto proj = new Projectile(avatar);
			auto collider = avatar->GetComponent<BoxColliderComponent>()->GetRectBounds();
			avatar->AddChild(proj);
			auto pos = avatar->GetTransform()->GetPosition2D();

			pos.y += collider.height / 4;
			proj->GetTransform()->SetPosition(pos.x, pos.y);
			AudioManager::GetService().PlaySFX(2, 10U, 0);
			proj->SetDirection(avatar->GetComponent<SpriteComponent>()->GetIsFlippedHorizontal() ? FVector2(1, 0) : FVector2(-1, 0));
		};
	};

	class JumpCommand final : public Command
	{
		virtual void Execute(GameObject* avatar) override
		{
			auto rigidbody = avatar->GetComponent<RigidBodyComponent>();
			rigidbody->AddVelocity(FVector2(0, 15.f));

		};
	};
}
