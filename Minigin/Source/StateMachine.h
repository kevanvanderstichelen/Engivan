#pragma once
#include "State.h"
#include <deque>
#include "Utilities.h"
namespace dae
{
	class StateMachine final
	{
	public:
		StateMachine() : m_pCurrent(new NullState()) {};
		StateMachine(State* current) : m_pCurrent(current) {}
		~StateMachine() { SAFE_DELETE(m_pCurrent); };
		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) noexcept = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) noexcept = delete;

		void SetCurrentState(State* current) { m_pCurrent = current; }
		void Update(float elapsed);
		void OnEnter();
		void OnExit();

	private:
		State* m_pCurrent = nullptr;
	};

	class StackedStateMachine final
	{
	public:
		StackedStateMachine() = default;
		~StackedStateMachine();
		StackedStateMachine(const StackedStateMachine& other) = delete;
		StackedStateMachine(StackedStateMachine&& other) noexcept = delete;
		StackedStateMachine& operator=(const StackedStateMachine& other) = delete;
		StackedStateMachine& operator=(StackedStateMachine&& other) noexcept = delete;

		void Push(State* state);
		void Pop();
		void Update(float elapsed);

	private:
		std::deque<State*> m_pStates{};
	};

}

