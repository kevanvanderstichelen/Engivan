#pragma once
#include "GameObject.h"
#include "StateMachine.h"
namespace dae
{
	class ZenChan final : public GameObject
	{
	public:
		ZenChan();
		virtual ~ZenChan();
		ZenChan(const ZenChan& other) = delete;
		ZenChan(ZenChan&& other) = delete;
		ZenChan& operator=(const ZenChan& other) = delete;
		ZenChan& operator=(ZenChan&& other) = delete;
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
		float m_JumpDelay = 1.5f;
		float m_RemoveThis = false;
	
		void CallBackTrigger(GameObject* current, GameObject* other);
		void CallBackCollision(GameObject* current, GameObject* other);
		void CallBackFrontBoxTrigger(GameObject* current, GameObject* other);
	};

}

