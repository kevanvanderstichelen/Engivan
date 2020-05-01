#pragma once
#include "BaseComponent.h"
#include <cmath> 
namespace dae
{
	class RigidBodyComponent final : public BaseComponent
	{
	public:
		RigidBodyComponent(const bool useGravity = true, const float mass = 1.f, const float gravity = -9.81f);

		virtual ~RigidBodyComponent() = default;
		RigidBodyComponent(const RigidBodyComponent& other) = delete;
		RigidBodyComponent(RigidBodyComponent&& other) noexcept = delete;
		RigidBodyComponent& operator=(const RigidBodyComponent& other) = delete;
		RigidBodyComponent& operator=(RigidBodyComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		void EnableGravity(const bool enable);

		void AddForce(const float x, const float y);
		void AddForce(const FVector2& force);
		void SetForce(const float x, const float y);
		void SetForce(const FVector2& force);

		void AddVelocity(const FVector2& velocity);

		const FVector2& GetVelocity() const noexcept { return m_LinearVelocity + m_Velocity; }
		const FVector2& GetForce() const noexcept { return m_Force; }
		const FVector2& GetAcceleration() const noexcept { return m_Acceleration; }

	public:
		friend class BoxColliderComponent;
		FVector2 m_LinearVelocity;
		FVector2 m_Velocity;
		bool m_UseGravity;
		const float m_Gravity;
		FVector2 m_Acceleration;
		float m_Mass;
		FVector2 m_Force;
		FVector2 m_Direction;
	};


}
