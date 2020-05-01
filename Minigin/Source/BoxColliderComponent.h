#pragma once
#include "BaseComponent.h"
#include <functional>
namespace dae
{
	class BoxColliderComponent final : public BaseComponent
	{
	public:
		BoxColliderComponent(const bool isStatic = true, const bool isTrigger = false);

		virtual ~BoxColliderComponent() = default;
		BoxColliderComponent(const BoxColliderComponent& other) = delete;
		BoxColliderComponent(BoxColliderComponent&& other) noexcept = delete;
		BoxColliderComponent& operator=(const BoxColliderComponent& other) = delete;
		BoxColliderComponent& operator=(BoxColliderComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		const void SetWidth(const float width) noexcept { m_Rectangle.width = width; }
		const void SetHeight(const float height) noexcept { m_Rectangle.height = height; }
		const bool IsStatic() const noexcept { return m_IsStatic; }
		const bool IsTrigger() const noexcept { return m_IsTrigger; }

		const FRect& GetRectBounds() const noexcept { return m_Rectangle; }

		void OnCollisionEnter(const BoxColliderComponent* other);
		const bool IsOverlapping(const BoxColliderComponent* other);

		typedef std::function<void(GameObject * triggerobject, GameObject * otherobject)> PhysicsCallback;

		void SetCollisionCallBack(PhysicsCallback callback) { m_CollisionCallBack = callback; }
		void SetTriggerCallBack(PhysicsCallback callback) { m_TriggerCallBack = callback; }

		const bool IsCollidingTop() const noexcept { return m_Penetrate.y < 0; }
		const bool IsCollidingBottom() const noexcept { return m_Penetrate.y > 0; }
		const bool IsCollidingLeft() const noexcept { return m_Penetrate.x > 0; }
		const bool IsCollidingRight() const noexcept { return m_Penetrate.x < 0; }

	private:
		static const std::string m_ComponentName;
		const bool m_IsStatic;
		bool m_IsTrigger;
		FRect m_Rectangle;
		PhysicsCallback m_CollisionCallBack;
		PhysicsCallback m_TriggerCallBack;
		FVector2 m_Penetrate;
	};


}
