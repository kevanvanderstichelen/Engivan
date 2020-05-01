#pragma once
#include "Command.h"
namespace dae
{
	class ShootCommand final : public Command
	{
		virtual void Execute(GameObject*) override
		{

		};
	};

	class JumpCommand final : public Command
	{
		virtual void Execute(GameObject* avatar) override
		{
			auto rigidbody = avatar->GetComponent<RigidBodyComponent>();
			auto collider = avatar->GetComponent<BoxColliderComponent>();
			if (collider->IsCollidingBottom()) rigidbody->AddVelocity(FVector2(0, 15.f));

		};
	};
}
