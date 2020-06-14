#include "MiniginPCH.h"
#include "State.h"
#include "StateMachine.h"

dae::State::~State()
{
	for (auto& transition : m_Transitions)
	{
		SAFE_DELETE(transition);
	}
}

void dae::State::RootUpdate(StateMachine* sm, float elapsed)
{
	if (!sm) return;

	for (auto& transition : m_Transitions)
	{
		if (transition->Check())
		{
			return sm->SetCurrentState(transition->GetTargetState());
		}
	}

	Update(sm, elapsed);
}

void dae::State::RootOnEnter(StateMachine* sm)
{
	if (!sm) return;

	OnEnter(sm);
}

void dae::State::RootOnExit(StateMachine* sm)
{
	if (!sm) return;

	OnExit(sm);
}