#pragma once
#include "Devlog.h"
#include <unordered_map>
#include <functional>
#include <vector>
namespace dae
{
	class StateMachine;
	class StackedStateMachine;
	class Transition;
	class State
	{
	public:
		virtual ~State();
		virtual void OnEnter(StateMachine* sm) = 0;
		virtual void OnExit(StateMachine* sm) = 0;
		virtual void Update(StateMachine* sm, float elapsed) = 0;
		void RootUpdate(StateMachine* sm, float elapsed);
		void RootOnEnter(StateMachine* sm);
		void RootOnExit(StateMachine* sm);

		void AddTransitions(std::vector<Transition*> transitions) {
			m_Transitions = transitions; 
		}

	private:
		std::vector<Transition*> m_Transitions{};
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

	class Transition final
	{
	public:
		explicit Transition(std::vector<std::function<bool()>> conditions, State* targetState)
			: m_Conditions(conditions), m_TargetState(targetState) {}

		const bool Check() const
		{
			int trueCounter = 0;
			for (auto& condition : m_Conditions)
			{
				if (condition()) trueCounter++;
			}
			return trueCounter == (int)m_Conditions.size();
		}

		State* GetTargetState() { return m_TargetState; }

	private:
		const std::vector<std::function<bool()>> m_Conditions;
		State* m_TargetState = nullptr;
	};

}
