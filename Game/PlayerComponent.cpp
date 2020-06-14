#include "MiniginPCH.h"
#include "PlayerComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "RigidBodyComponent.h"
#include "InputManager.h"
#include "Command.h"
#include "SceneManager.h"
#include "GameStates.h"
#include "UIComponent.h"

dae::PlayerComponent::PlayerComponent(UIComponent* ui, const float moveSpeed, const float jumpSpeed, const uint id)
	:m_MoveSpeed(moveSpeed), m_JumpSpeed(jumpSpeed)
	, m_MaxLives(4), m_CurrentLives(m_MaxLives)
	,m_FSM(), m_ID(id)
	,m_UI(ui)
{
}

void dae::PlayerComponent::Initialize()
{

	State* moveState = new MoveState();
	State* shootState = new ShootState();
	State* jumpState = new JumpState();
	State* deadState = new DeadState();
	State* idleState = new IdleState();

	auto& input = InputManager::GetInstance();
	auto idleCondition = [this, &input]() { return input.GetControllerLeftAxis(m_ID).x == 0 && input.GetControllerLeftAxis(m_ID).y == 0; };
	auto moveCondition = [this, &input]() { return input.GetControllerLeftAxis(m_ID).x != 0 || input.GetControllerLeftAxis(m_ID).y != 0; };
	auto shootCondition = [this, &input]() { return input.IsControllerPressedDown(XBOXButton::RB, m_ID); };
	auto jumpCondition = [this, &input]() { return input.IsControllerPressedDown(XBOXButton::A, m_ID); };
	auto deadCondition = [this]() { return m_pGameObject->GetComponent<HealthComponent>()->IsDead(); };
	auto respawnCondition = [this]() { return m_pGameObject->GetComponent<SpriteComponent>()->IsFullAnimationPlayed(); };

	idleState->AddTransitions(
		{ new Transition({moveCondition}, moveState),
		  new Transition({shootCondition}, shootState),
		  new Transition({jumpCondition}, jumpState),
		  new Transition({deadCondition}, deadState), } );

	moveState->AddTransitions(
		{ new Transition({idleCondition}, idleState),
		  new Transition({shootCondition}, shootState),
		  new Transition({jumpCondition}, jumpState),
		  new Transition({deadCondition}, deadState), } );

	shootState->AddTransitions(
		{ new Transition({idleCondition}, idleState),
		  new Transition({moveCondition}, moveState),
		  new Transition({jumpCondition}, jumpState),
		  new Transition({deadCondition}, deadState), });

	jumpState->AddTransitions(
		{ new Transition({idleCondition}, idleState),
		  new Transition({moveCondition}, moveState),
		  new Transition({shootCondition}, shootState),
		  new Transition({jumpCondition}, jumpState),
		  new Transition({deadCondition}, deadState), });

	deadState->AddTransitions(
		{ new Transition({respawnCondition}, idleState) }
	);

	m_FSM.Initialize(idleState, m_pGameObject);
	m_FSM.AddStates({ moveState, shootState, jumpState, deadState,idleState });


	
}

void dae::PlayerComponent::Update(float elapsed)
{
	m_FSM.Update(elapsed);

	//Flip avatar image (facing right/left)
	auto& input = InputManager::GetInstance();
	auto axis = input.GetControllerLeftAxis(m_ID);
	if (axis.x > 0) m_pGameObject->GetComponent<SpriteComponent>()->FlipHorizontal(true);
	else if (axis.x < 0) m_pGameObject->GetComponent<SpriteComponent>()->FlipHorizontal(false);

	auto collider = m_pGameObject->GetComponent<BoxColliderComponent>();
	auto rigid = m_pGameObject->GetComponent<RigidBodyComponent>();
	if (rigid->GetLinearVelocity().y > 0)
	{
		collider->Enable(false);
	}
	else
	{
		collider->Enable(true);
	}


}

void dae::PlayerComponent::Render()
{

}

const std::string dae::PlayerComponent::GetComponentName() const
{
	return std::string();
}

void dae::PlayerComponent::AddScore(const int& score)
{
	if (m_UI)
	{
		m_CurrentScore += score;
		m_UI->UpdateScore(m_ID, m_CurrentScore);
	}
}

