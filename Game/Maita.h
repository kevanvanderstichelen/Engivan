#pragma once
#include "GameObject.h"
#include "StateMachine.h"
namespace dae
{
	class Maita final : public GameObject
	{
	public:
		Maita();
		virtual ~Maita();
		Maita(const Maita& other) = delete;
		Maita(Maita&& other) = delete;
		Maita& operator=(const Maita& other) = delete;
		Maita& operator=(Maita&& other) = delete;
	protected:
		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;
	private:
		GameObject* m_pTarget;
		GameObject* m_pFrontBox;
		StateMachine m_FSM;
		bool m_Popped = false;
		bool m_IsFlipped = false;
		float m_FlipDelay = 0.5f;
		float m_FlipElapsed = 0.0f;
		float m_JumpElapsed = 0.0f;
		float m_JumpDelay = 2.f;
		float m_RemoveThis = false;

		void CallBackTrigger(GameObject* current, GameObject* other);
		void CallBackCollision(GameObject* current, GameObject* other);
		void CallBackFrontBoxTrigger(GameObject* current, GameObject* other);
	};

}