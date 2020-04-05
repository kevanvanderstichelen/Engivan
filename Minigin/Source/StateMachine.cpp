#include "MiniginPCH.h"
#include "StateMachine.h"

#pragma region STATE-MACHINE

void dae::StateMachine::Update(float elapsed)
{
	m_pCurrent->Update(this, elapsed);
}

void dae::StateMachine::OnEnter()
{
	m_pCurrent->OnEnter(this);
}

void dae::StateMachine::OnExit()
{
	m_pCurrent->OnExit(this);
}

#pragma region STATE-MACHINE

#pragma region STACKED-STATE-MACHINE

dae::StackedStateMachine::~StackedStateMachine()
{
	for (State* pState : m_pStates)
	{
		SAFE_DELETE(pState);
	}
}

void dae::StackedStateMachine::Push(State* state)
{
	state->OnEnter(nullptr);
	m_pStates.push_back(std::move(state));
}

void dae::StackedStateMachine::Pop()
{
	if (!m_pStates.empty())
	{
		m_pStates.back()->OnExit(nullptr);
		m_pStates.pop_back();
	}
}

void dae::StackedStateMachine::Update(float elapsed)
{
	if (!m_pStates.empty())
	{
		m_pStates.back()->Update(nullptr, elapsed);
	}
}

#pragma endregion STACKED-STATE-MACHINE