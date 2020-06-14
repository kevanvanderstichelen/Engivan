#pragma once
#include "GameObject.h"
#include "MainStructs.h"
namespace dae
{
	class SpriteComponent;
	class EnemyProjectile final : public GameObject
	{
	public:
		explicit EnemyProjectile(GameObject* shotFrom);
		virtual ~EnemyProjectile();
		EnemyProjectile(const EnemyProjectile& other) = delete;
		EnemyProjectile(EnemyProjectile&& other) = delete;
		EnemyProjectile& operator=(const EnemyProjectile& other) = delete;
		EnemyProjectile& operator=(EnemyProjectile&& other) = delete;
		void SetDirection(const FVector2& direction) { m_Direction = direction; }

	protected:
		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;
	private:
		GameObject* m_pLinkedGameObject;
		const float m_Speed = 580.f;
		const float m_EndExistanceTime = 1.f;
		float m_EndElapsed = 0.0f;
		bool m_IsValid = true;
		FVector2 m_Direction;
		void CallBack(GameObject* current, GameObject* other);

	};

}