#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

const std::string dae::TextComponent::m_ComponentName{ "TextComponent" };

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_Color{ 255,255,255 }
{
}

dae::TextComponent::TextComponent(const std::string& text, const std::shared_ptr<Font>& font, const SDL_Color& color)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr), m_Color{ color }
{
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
		SDL_FreeSurface(surf);
		m_pTexture = std::make_shared<Texture2D>(texture);
		m_NeedsUpdate = false;
	}
}

void dae::TextComponent::Render()
{
	if (m_pTexture != nullptr)
	{
		const auto pos = m_pGameObject->GetTransformComponent()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
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
