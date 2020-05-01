#pragma once
#include "MiniginPCH.h"
#include "BaseComponent.h"
#include "TextComponent.h"
#include "Utilities.h"
#include "ResourceManager.h"
namespace dae
{
	class FPSComponent final : public BaseComponent
	{
	public:
		FPSComponent(const FColor4& color = FColor4(1, 1, 0, 1), Font* font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18));

		virtual ~FPSComponent();
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) noexcept = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) noexcept = delete;

		void Initialize() override;
		void Update(float elapsed) override;
		void Render() override;
		virtual const std::string GetComponentName() const;

	private:
		static const std::string m_ComponentName;
		GameObject* m_FPSObject;
		Font* m_pFont;
		FColor4 m_Color;
	};


}
