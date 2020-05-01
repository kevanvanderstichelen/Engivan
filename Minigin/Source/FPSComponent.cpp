#include "MiniginPCH.h"
#include "TextComponent.h"
#include "FPSComponent.h"
#include "Utilities.h"
#include "Scene.h"
#include "TransformComponent.h"

const std::string dae::FPSComponent::m_ComponentName{ "FPSComponent" };

dae::FPSComponent::FPSComponent(const FColor4& color, Font* font)
	:m_Color(color), m_pFont(font), m_FPSObject(new GameObject()) {}

dae::FPSComponent::~FPSComponent() { }

void dae::FPSComponent::Initialize()
{
	SDL_Color color;
	color.r = Uint8(m_Color.r * 255);
	color.g = Uint8(m_Color.g * 255);
	color.b = Uint8(m_Color.b * 255);
	color.a = Uint8(m_Color.a * 255);

	m_FPSObject->AddComponent(new TextComponent("0 FPS", m_pFont, color));
	SCENEMANAGER.GetActiveScene().Add(m_FPSObject);
}

void dae::FPSComponent::Update(float )
{
	m_FPSObject->GetTransform()->SetPosition(m_pGameObject->GetTransform()->GetPosition());

	if (TIME.m_ElapsedFPS >= 0.99f)
	{
		m_FPSObject->GetComponent<TextComponent>()->SetText(std::to_string(TIME.m_FPS) + " FPS");
	}
}

void dae::FPSComponent::Render(){}

const std::string dae::FPSComponent::GetComponentName() const
{
	return m_ComponentName;
}
