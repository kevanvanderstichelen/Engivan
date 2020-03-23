#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"

const std::string dae::SpriteComponent::m_ComponentName{ "SpriteComponent" };

dae::SpriteComponent::SpriteComponent()
{
}

void dae::SpriteComponent::Initialize()
{
}

void dae::SpriteComponent::Update(float)
{
}

void dae::SpriteComponent::Render()
{
	const auto pos = m_pGameObject->GetTransformComponent()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
}

const std::string dae::SpriteComponent::GetComponentName() const
{
	return m_ComponentName;
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
	m_Texture = ResourceManager::GetInstance().LoadTexture(filename);
}
