#pragma once
//#include "MainStructs.h"
#include "MiniginPCH.h"
#include "BaseComponent.h"

namespace dae
{
	class CameraComponent final : public BaseComponent
	{
	public:
		CameraComponent();
		CameraComponent(const FPoint2& position, const int width, const int height);

		virtual ~CameraComponent();
		CameraComponent(const CameraComponent& other) = delete;
		CameraComponent(CameraComponent&& other) noexcept = delete;
		CameraComponent& operator=(const CameraComponent& other) = delete;
		CameraComponent& operator=(CameraComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		const FPoint2& GetPosition() const { return m_Position; }
		void SetPosition(const FVector2& pos);
		void Translate(const FVector2& pos);

		void AddToScreen(GameObject* gameObject);

		void Begin();
		void End();

	private:
		static const std::string m_ComponentName;
		const int m_Width, m_Height;
		FPoint2 m_Position;
		std::vector<GameObject*> m_pScreenObjects;
	};

}
