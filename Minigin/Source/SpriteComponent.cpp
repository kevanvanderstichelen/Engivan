#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "Utilities.h"

const std::string dae::SpriteComponent::m_ComponentName{ "SpriteComponent" };

dae::SpriteComponent::SpriteComponent()
{
}

dae::SpriteComponent::~SpriteComponent()
{
	SAFE_DELETE(m_pTexture);
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
	//Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	FRect dest;
	dest.bottom = pos.y;
	dest.left = pos.x;
	dest.width = m_pTexture->GetWidth();
	dest.height = m_pTexture->GetHeight();
	FRect src;
	src.width = 1;
	src.height = -1;
	Renderer::GetInstance().RenderTexture2D(m_pTexture, dest, src);
}

const std::string dae::SpriteComponent::GetComponentName() const
{
	return m_ComponentName;
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadImageTexture(filename);
}
