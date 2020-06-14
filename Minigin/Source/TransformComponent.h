#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent();
		TransformComponent(const FVector3& position);
		TransformComponent(const FVector3& position, const float rotation);
		TransformComponent(const FVector3& position, const float rotation, const float scale);

		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void SetPosition(const float x, const float y);
		void SetPosition(const float x, const float y, const float z);
		void SetPosition(const FVector3& position);
		void SetScale(const float scale);
		void SetRotation(const float rotation);

		void Translate(const float x, const float y);
		void Translate(const FVector2& pos);
		void Translate(const float x, const float y, const float z);
		void Translate(const FVector3& pos);
		void TranslateX(const float x);
		void TranslateY(const float y);

		virtual const std::string GetComponentName() const;

		const FVector3 GetPosition() const;
		const FPoint2 GetPosition2D() const;

		const float GetScale() const;
		const float GetRotation() const;

		void Initialize() override;
		void Update(float elapsed) override;
		void Render() override;

	private:
		static const std::string m_ComponentName;
		FVector3 m_Position;
		float m_Scale;
		float m_Rotation;
		FVector3 m_Pivot;
		FPoint2 m_Translate;

	};

	inline TransformComponent& operator+=(TransformComponent& pTransform, TransformComponent& pTransformRight)
	{
		auto totPos = pTransform.GetPosition() + pTransformRight.GetPosition();
		auto totRot = pTransform.GetRotation() + pTransformRight.GetRotation();
		auto totScale = pTransform.GetScale() * pTransformRight.GetScale();
		pTransform.SetPosition(totPos);
		pTransform.SetRotation(totRot);
		pTransform.SetScale(totScale);
		return pTransform;
	}

}


