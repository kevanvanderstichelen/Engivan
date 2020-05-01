#include "MiniginPCH.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "Utilities.h"
#include "ResourceManager.h"

const std::string dae::TextComponent::m_ComponentName{ "TextComponent" };

dae::TextComponent::TextComponent(const std::string& text, Font* font, TextAllignment allignment)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr)
	, m_Color{ 255,255,255 }, m_Allignment{ allignment } {}

dae::TextComponent::TextComponent(const std::string& text, Font* font, const SDL_Color& color, TextAllignment allignment)
	: m_NeedsUpdate(true), m_Text(text), m_pFont(font), m_pTexture(nullptr)
	, m_Color{ color }, m_Allignment{ allignment } {}

dae::TextComponent::~TextComponent()
{
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
		//Get transform
		const auto& position = m_pGameObject->GetTransform()->GetPosition();
		const auto& scale = m_pGameObject->GetTransform()->GetScale();
		const auto& rotation = m_pGameObject->GetTransform()->GetRotation();

		//SRC = animted, DEST = POS
		FRect src;
		src.width = (float)m_pTexture->GetWidth();
		src.height = (float)m_pTexture->GetHeight();
		src.left = src.width;
		src.bottom = src.height;

		FRect dest{ 0,0,src.width,src.height };

		//Draw sprite with & applying transform position/scale/rotation
		glPushMatrix();

		switch (m_Allignment)
		{
		case TextAllignment::Left:
			glTranslatef(position.x, position.y, 0);
			break;
		case TextAllignment::Middle:
			glTranslatef(position.x - (src.width / 2), position.y, 0);
			break;
		case TextAllignment::Right:
			glTranslatef(position.x - src.width, position.y, 0);
			break;
		}

		glRotatef(rotation, 0, 0, 1);
		glScalef(scale, scale, 0);
		Renderer::GetInstance().RenderTexture2D(m_pTexture, dest, src);
		glPopMatrix();

	}
}

const std::string dae::TextComponent::GetComponentName() const
{
	return m_ComponentName;
}

void dae::TextComponent::SetText(const std::string& text)
{
	if (m_Text == text) return;
	m_Text = text;
	m_NeedsUpdate = true;
}

void dae::TextComponent::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void dae::TextComponent::SetColor(const FColor4& color)
{
	float fR, fG, fB, fA;
	fR = color.r * 255.f;
	fG = color.g * 255.f;
	fB = color.b * 255.f;
	fA = color.a * 255.f;
	Uint8 r, g, b, a;
	r = (Uint8)fR;
	g = (Uint8)fG;
	b = (Uint8)fB;
	a = (Uint8)fA;
	m_Color.r = r;
	m_Color.g = g;
	m_Color.b = b;
	m_Color.a = a;
}
