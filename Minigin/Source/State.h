#pragma once
#include "Devlog.h"
namespace dae
{
	class StateMachine;
	class StackedStateMachine;

	class State
	{
	public:
		virtual ~State() = default;
		virtual void OnEnter(StateMachine* sm) = 0;
		virtual void OnExit(StateMachine* sm) = 0;
		virtual void Update(StateMachine* sm, float elapsed) = 0;
	};

	class NullState final : public State
	{
		virtual void OnEnter(StateMachine*) override
		{
			Devlog::GetInstance().PrintWarning("State::NullState::OnEnter() - No derrived state class assigned on base class StateMachine!");
		}
		virtual void OnExit(StateMachine*) override
		{
			Devlog::GetInstance().PrintWarning("State::NullState::OnExit() - No derrived state class assigned on base class StateMachine!");
		}
		virtual void Update(StateMachine*, float) override
		{
			Devlog::GetInstance().PrintWarning("State::NullState::Update() - No derrived state class assigned on base class StateMachine!");
		}
	};

}
