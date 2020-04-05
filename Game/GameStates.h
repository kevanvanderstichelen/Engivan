#pragma once
#include "State.h"
#include "StateMachine.h"

namespace dae
{
	class MoveState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void OnExit(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			if (!sm) return;
		}
	};

	class ShootState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void OnExit(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			if (!sm) return;
		}
	};

	class JumpState : public State
	{
		virtual void OnEnter(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void OnExit(StateMachine* sm) override
		{
			if (!sm) return;
		}
		virtual void Update(StateMachine* sm, float elapsed) override
		{
			if (!sm) return;
		}
	};
}
