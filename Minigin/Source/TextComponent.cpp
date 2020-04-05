#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Utilities.h"
#include "ResourceManager.h"

const std::string dae::TextComponent::m_ComponentName{ "TextComponent" };

dae::TextComponent::TextComponent(const std::string& text, Font* font)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_Color{ 255,255,255 }
{
}

dae::TextComponent::TextComponent(const std::string& text, Font* font, const SDL_Color& color)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_Color{ color }
{
}

dae::TextComponent::~TextComponent()
{
	SAFE_DELETE(m_pFont);
	SAFE_DELETE(m_pTexture);
}

void dae::TextComponent::Initialize()
{

}

void dae::TextComponent::Update(float elapsed)
{
	UNREFERENCED_PARAMETER(elapsed);
	if (m_NeedsUpdate)
	{
		const auto& surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), m_Color);

		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}

		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}

		SAFE_DELETE(m_pTexture);
		m_pTexture = ResourceManager::GetInstance().CreateFromSurface(surf);
		m_NeedsUpdate = false;
		SDL_FreeSurface(surf);
	}
}

void dae::TextComponent::Render()
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetTransformComponent()->GetPosition();
		FRect dest;
		dest.bottom = pos.x;
		dest.left = pos.y;
		dest.width = m_pTexture->GetWidth();
		dest.height = m_pTexture->GetHeight();
		FRect src;
		src.bottom = 1;
		src.width = 1;
		Renderer::GetInstance().RenderTexture2D(m_pTexture, dest, src);

	}
}

const std::string dae::TextComponent::GetComponentName() const
{
	return m_ComponentName;
}

void dae::TextComponent::SetText(const std::string& text)
{
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}
