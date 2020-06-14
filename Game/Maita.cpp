#include "Maita.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "GridComponent.h"
#include "BoxColliderComponent.h"
#include "RigidBodyComponent.h"
#include "GameStates.h"
#include "HealthComponent.h"
#include "Scene.h"
#include "Pickup.h"

dae::Maita::Maita()
{
}

dae::Maita::~Maita()
{
}

void dae::Maita::Initialize()
{
	//SEARCH FOR NEAREST PLAYER SET THAT AS TARGET.
	auto scene = static_cast<BubbleBobbleScene*>(GetLinkedScene());
	auto& players = scene->GetPlayers();

	float nearestDist = FLT_MAX;

	for (size_t i = 0; i < players.size(); i++)
	{
		FVector2 v1, v2;
		v1.x = players[i]->GetTransform()->GetPosition2D().x;
		v1.y = players[i]->GetTransform()->GetPosition2D().y;
		v2.x = GetTransform()->GetPosition2D().x;
		v2.y = GetTransform()->GetPosition2D().y;

		if (Distance(v1, v2) < nearestDist)
		{
			nearestDist = Distance(v1, v2);
			m_pTarget = players[i];
		}

	}


	//MAIN INITILIZE
	SetTag("Enemy");
	GetTransform()->SetScale(2.f);

	auto sprite = new SpriteComponent("Character/Maita/Maita.png", 25, 25, 10);
	sprite->AddSpriteAnimation(new SpriteAnimation(5U, 1), "Walk");
	sprite->AddSpriteAnimation(new SpriteAnimation(5U, 2), "Shoot");
	sprite->AddSpriteAnimation(new SpriteAnimation(3U, 3), "FloatingGreen");
	sprite->AddSpriteAnimation(new SpriteAnimation(3U, 4), "FloatingBlue");
	sprite->AddSpriteAnimation(new SpriteAnimation(4U, 5), "Dead");
	sprite->FlipHorizontal(true);
	AddComponent(sprite);

	AddComponent(new GridComponent());
	AddComponent(new HealthComponent(1, 1));
	//SET CALLBACKS
	auto collider = new BoxColliderComponent(false, false);
	collider->SetTriggerCallBack(std::bind(&Maita::CallBackTrigger, this, std::placeholders::_1, std::placeholders::_2));
	collider->SetCollisionCallBack(std::bind(&Maita::CallBackCollision, this, std::placeholders::_1, std::placeholders::_2));
	AddComponent(collider);

	AddComponent(new RigidBodyComponent(true));

	//[ FINITE STATE MACHINE ] STATES
	State* moveState = new EnemyMoveState();
	State* floatState = new EnemyFloatState();
	State* spinState = new EnemySpinState();
	State* jumpState = new EnemyJumpState();
	State* shootState = new EnemyShootState();

	//[ FINITE STATE MACHINE ] CONDITIONS
	auto deadCondition = [this]() { return GetComponent<HealthComponent>()->IsDead(); };
	auto popBubbleCondition = [this]() { return m_Popped; };
	auto jumpCondition = [this]()
	{
		auto colllider = GetComponent< BoxColliderComponent>();
		if (m_pTarget->GetTransform()->GetPosition().y > (GetTransform()->GetPosition().y + colllider->GetRectBounds().height)
			&& m_JumpElapsed >= m_JumpDelay)
		{
			m_JumpElapsed = 0.0f;
			return true;
		}
		return false;
	};

	auto stopJumpCondition = [this]() {return GetComponent<RigidBodyComponent>()->GetLinearVelocity().y > 0; };
	auto shootCondition = [this]() 
	{
		auto sprite = GetComponent<SpriteComponent>();
		auto target = m_pTarget->GetTransform()->GetPosition();
		auto current = GetTransform()->GetPosition();

		float delta = current.x - target.x;

		float deltaY = abs(current.y - target.y);
		
		if (deltaY >= 10)
		{
			return false;
		}

		if (delta < 0 && sprite->GetIsFlippedHorizontal())
		{
			return true;
		}

		if (delta > 0 && !sprite->GetIsFlippedHorizontal())
		{
			return true;
		}
		return false;
	};
	auto stopShootCondition = [this]() {return GetComponent<SpriteComponent>()->IsFullAnimationPlayed(); };

	//[ FINITE STATE MACHINE ] TRANSITIONS
	moveState->AddTransitions(
		{ new Transition({deadCondition}, floatState),
		  new Transition({jumpCondition}, jumpState),
		  new Transition({shootCondition}, shootState) }
	);

	floatState->AddTransitions(
		{ new Transition({popBubbleCondition}, spinState) });

	jumpState->AddTransitions(
		{ new Transition({deadCondition}, floatState),
		new Transition({stopJumpCondition}, moveState) });

	shootState->AddTransitions(
		{ new Transition({deadCondition}, floatState),
		  new Transition({stopShootCondition}, moveState) });


	//[ FINITE STATE MACHINE ] INIT
	m_FSM.Initialize(moveState, this);
	m_FSM.AddStates({ moveState, floatState, spinState, jumpState, shootState});

	//FRONT BOX USED FOR PURPOSE FLIPPING THE ENEMY TO SWEEP LEFT - > RIGHT...
	m_pFrontBox = new GameObject();
	m_pFrontBox->SetTag("Ignore");
	auto frontBoxCollider = new BoxColliderComponent(false, true);
	frontBoxCollider->SetHeight(10.f);
	frontBoxCollider->SetWidth(10.f);
	frontBoxCollider->SetTriggerCallBack(std::bind(&Maita::CallBackFrontBoxTrigger, this, std::placeholders::_1, std::placeholders::_2));
	m_pFrontBox->AddComponent(frontBoxCollider);
	AddChild(m_pFrontBox);
}

void dae::Maita::Update(float elapsed)
{
	m_FSM.Update(elapsed);

	//GET ALL REQUIRED COMPONENTS FOR FOLLOWING CALCULATIONS
	auto currentPos = GetTransform()->GetPosition();
	auto isFlipped = GetComponent<SpriteComponent>()->GetIsFlippedHorizontal();
	auto collider = GetComponent<BoxColliderComponent>();
	auto rigid = GetComponent<RigidBodyComponent>();
	auto colliderFrontBox = m_pFrontBox->GetComponent< BoxColliderComponent>();

	//WHEN TEXTURE IS FLIPPED -> FRONT BOX HAS TO FLIP TOO
	if (isFlipped) currentPos.x += collider->GetRectBounds().width + 1;
	else currentPos.x -= colliderFrontBox->GetRectBounds().width + 1;

	//ADD THE HEIGHT OF THE FRONTBOX AND DEFINE ITS POSITION RELEVANT WITH ZENCHAN'S TRANSFORM
	currentPos.y += colliderFrontBox->GetRectBounds().height + 1;
	m_pFrontBox->GetTransform()->SetPosition(currentPos);

	//DELAYS FOR FLIPPING TEX IMAGE & JUMPING WHEN TARGET IS HIGHER
	if (m_FlipElapsed <= m_FlipDelay) m_FlipElapsed += elapsed;
	if (m_JumpElapsed <= m_JumpDelay) m_JumpElapsed += elapsed;

	//DISSABLE COLLIDER WHEN JUMPING
	rigid->GetLinearVelocity().y > 0 ? collider->Enable(false) : collider->Enable(true);

	if (m_RemoveThis)
	{
		auto pickup = new Pickup("Fries", 200);
		pickup->RootInitialize();
		pickup->GetTransform()->SetPosition(GetTransform()->GetPosition());
		SCENEMANAGER.GetActiveScene().Add(pickup);
		SCENEMANAGER.GetActiveScene().Remove(this);
	}
}

void dae::Maita::Render() const
{
}

void dae::Maita::CallBackTrigger(GameObject* , GameObject* other)
{
	//WHEN PLAYER IS COLLIDNG THAN ITS POPPED AND DROPS LOOT AFTER THIS.
	if (m_Popped) return;
	if (other->GetTag() == "Player") m_Popped = true;
}

void dae::Maita::CallBackCollision(GameObject* , GameObject* other)
{
	if (m_Popped)
	{
		//WHEN POPPED SPWN PICKUP AND REMOVE THIS OBJECT FROM SCENE
		if (other->GetTag() != "Player")
		{
			m_RemoveThis = true;
		}
	}
	else
	{
		//DO DAMAGE WITH COLLIDES WITH PLAYER
		if (other->GetTag() == "Player") other->GetComponent<HealthComponent>()->DoDamage();
	}
}

void dae::Maita::CallBackFrontBoxTrigger(GameObject* , GameObject* other)
{
	if (other->GetTag() == "Player" || other->GetTag() == "Projectile") return;

	//FLIP ENEMY (FACING) SO IT WANDERS THE OPPOSITE WAY
	if (m_FlipElapsed >= m_FlipDelay)
	{
		GetComponent<SpriteComponent>()->FlipHorizontal(m_IsFlipped);
		m_IsFlipped = !m_IsFlipped;
		m_FlipElapsed = 0;
	}
}