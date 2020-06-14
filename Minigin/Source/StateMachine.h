#pragma once
#include "State.h"
#include <deque>
#include "Utilities.h"
namespace dae
{


	class StateMachine final
	{
	public:
		StateMachine() = default;
		~StateMachine() 
		{ 
			for (auto& state : m_pStates)
			{
				SAFE_DELETE(state);
			}

		};
		StateMachine(const StateMachine& other) = delete;
		StateMachine(StateMachine&& other) noexcept = delete;
		StateMachine& operator=(const StateMachine& other) = delete;
		StateMachine& operator=(StateMachine&& other) noexcept = delete;

		void SetCurrentState(State* current);
		void Update(float elapsed);
		void OnEnter();
		void OnExit();

		void AddState(State* pState) { m_pStates.push_back(pState); }
		void AddStates(std::vector<State*> pStates) { m_pStates = pStates; }

		GameObject* GetGameObject() const { return m_pGameObject; }

		void Initialize(State* pStartState, GameObject* linkedObject)
		{
			m_pGameObject = linkedObject;
			m_pCurrent = pStartState;
			m_pCurrent->OnEnter(this);
		}
	private:
		std::vector<State*> m_pStates;

		State* m_pCurrent = nullptr;
		GameObject* m_pGameObject = nullptr;
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

