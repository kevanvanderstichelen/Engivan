#pragma once
#include "GameObject.h"
#include "MainStructs.h"
namespace dae
{
	class SpriteComponent;
	class Projectile final : public GameObject
	{
	public:
		explicit Projectile(GameObject* shotFrom);
		virtual ~Projectile();
		Projectile(const Projectile& other) = delete;
		Projectile(Projectile&& other) = delete;
		Projectile& operator=(const Projectile& other) = delete;
		Projectile& operator=(Projectile&& other) = delete;
		void SetDirection(const FVector2& direction) { m_Direction = direction; }

	protected:
		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;
	private:
		GameObject* m_pLinkedGameObject;
		const float m_Speed = 680.f;
		const float m_EndExistanceTime = 1.f;
		float m_EndElapsed = 0.0f;
		bool m_IsValid = true;
		FVector2 m_Direction;
		void CallBack(GameObject* current, GameObject* other);

	};

}

