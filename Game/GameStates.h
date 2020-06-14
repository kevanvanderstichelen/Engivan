#pragma once
#include "State.h"
#include "StateMachine.h"
#include "PlayerComponent.h"
#include "StateMachine.h"
#include "InputManager.h"
#include "HealthComponent.h"
#include "Command.h"
#include "BubbleBobbleScene.h"
#include "AudioManager.h"
#include "EnemyProjectile.h"

namespace dae
{
	class IdleState final : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayAnimation("Idle");

		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			UNREFERENCED_PARAMETER(sm);
			UNREFERENCED_PARAMETER(elapsed);
			auto spriteComponent = sm->GetGameObject()->GetComponent<SpriteComponent>();
			auto rigidbodyComponent = sm->GetGameObject()->GetComponent<RigidBodyComponent>();
			if (!spriteComponent || !rigidbodyComponent) return;

			const FVector2& curVel = rigidbodyComponent->GetLinearVelocity();
			if (curVel.y > 0)
			{
				spriteComponent->PlayAnimation("JumpUp");
			}
			else if (curVel.y < 0)
			{
				spriteComponent->PlayAnimation("JumpDown");
			}
			else
			{
				spriteComponent->PlayAnimation("Idle");
			}
			
		}
	};

	class MoveState final : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayAnimation("Walk");

			
		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			PlayerComponent* playerComponent = gameObject->GetComponent<PlayerComponent>();

			if (!playerComponent) return;
			auto& input = InputManager::GetInstance();
			auto axis = input.GetControllerLeftAxis(playerComponent->GetID());
			gameObject->GetTransform()->TranslateX(axis.x * elapsed * 180.f);

			auto spriteComponent = sm->GetGameObject()->GetComponent<SpriteComponent>();
			auto rigidbodyComponent = sm->GetGameObject()->GetComponent<RigidBodyComponent>();
			if (!spriteComponent || !rigidbodyComponent) return;

			const FVector2& curVel = rigidbodyComponent->GetLinearVelocity();
			if (curVel.y > 0)
			{
				spriteComponent->PlayAnimation("JumpUp");
			}
			else if (curVel.y < 0)
			{
				spriteComponent->PlayAnimation("JumpDown");
			}
			else
			{
				spriteComponent->PlayAnimation("Walk");
			}

		}
	};

	class ShootState final : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayFullAnimation("Shoot");


			auto& input = InputManager::GetInstance();
			input.GetCommand(XBOXButton::RB)->Execute(gameObject);



		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float ) override
		{
			UNREFERENCED_PARAMETER(sm);

		}
	};

	class JumpState final : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			auto& input = InputManager::GetInstance();
			input.GetCommand(XBOXButton::A)->Execute(gameObject);
			
		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float ) override
		{
			UNREFERENCED_PARAMETER(sm);

		}

	};

	class DeadState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayFullAnimation("Dead");

		}
		virtual void OnExit(StateMachine* sm) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			auto player = gameObject->GetComponent<PlayerComponent>();
			auto health = gameObject->GetComponent<HealthComponent>();
			health->Reset();
			auto scene = static_cast<BubbleBobbleScene*>(&SCENEMANAGER.GetActiveScene());
			auto pos = scene->GetSpawnPoint(player->GetID());
			gameObject->GetTransform()->SetPosition(pos.x, pos.y);
			player->DeductLife();
			if (player->GetCurrentLives() <= 0)
			{
				gameObject->SetActive(false);
			}
		}
		virtual void Update(StateMachine* sm, float ) override
		{
			UNREFERENCED_PARAMETER(sm);
		}

	};

	class EnemyMoveState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayAnimation("Walk");

		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			UNREFERENCED_PARAMETER(sm);

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;
			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;


			float speed = 50.f;
			spriteComponent->GetIsFlippedHorizontal() ? speed *= 1 : speed *= -1;
			gameObject->GetTransform()->TranslateX(speed * elapsed);
		}

	};

	class EnemyJumpState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			auto rigidbody = gameObject->GetComponent<RigidBodyComponent>();
			rigidbody->AddVelocity(FVector2(0, 15.f));

		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
	};

	class EnemyShootState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			gameObject->GetComponent<SpriteComponent>()->PlayFullAnimation("Shoot");

		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;


			auto proj = new EnemyProjectile(gameObject);
			gameObject->AddChild(proj);
			auto pos = gameObject->GetTransform()->GetPosition2D();
			pos.y += 1;
			proj->GetTransform()->SetPosition(pos.x, pos.y);

			proj->SetDirection(gameObject->GetComponent<SpriteComponent>()->GetIsFlippedHorizontal() ? FVector2(1, 0) : FVector2(-1, 0));
		}
		virtual void Update(StateMachine* sm, float) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
	};


	class EnemyFloatState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			auto health = gameObject->GetComponent<HealthComponent>();

			auto other = health->GetLinkedObject();

			uint otherId = other->GetComponent<PlayerComponent>()->GetID();

			if (otherId == 0)
			{
				spriteComponent->PlayFullAnimation("FloatingGreen");
			}
			else
			{
				spriteComponent->PlayFullAnimation("FloatingBlue");
			}
			

			auto collider = gameObject->GetComponent<BoxColliderComponent>();
			collider->SetIsTrigger(true);
			//collider->Enable(true);

			auto rigid = gameObject->GetComponent<RigidBodyComponent>();
			rigid->EnableGravity(false);

			rigid->SetVelocity(FVector2(0, 0));
			rigid->SetLinearVelocity(FVector2(0, 0));

			AudioManager::GetService().PlaySFX(3, 10U, 0);

		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			UNREFERENCED_PARAMETER(sm);
			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			gameObject->GetTransform()->TranslateY(elapsed * 30.f);


		}

	};


	class EnemySpinState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{

			GameObject* gameObject = sm->GetGameObject();

			if (!gameObject) return;

			SpriteComponent* spriteComponent = gameObject->GetComponent<SpriteComponent>();

			if (!spriteComponent) return;

			spriteComponent->PlayAnimation("Dead");

			auto collider = gameObject->GetComponent<BoxColliderComponent>();
			collider->SetIsTrigger(false);

			auto rigid = gameObject->GetComponent<RigidBodyComponent>();
			rigid->EnableGravity(true);

			//rigid->AddVelocity(FVector2(0, 15.f));
		}
		virtual void OnExit(StateMachine* sm) override
		{
			UNREFERENCED_PARAMETER(sm);
		}
		virtual void Update(StateMachine* sm, float) override
		{
			UNREFERENCED_PARAMETER(sm);
		}

	};
}
