#include "MiniginPCH.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "TransformComponent.h"
#include "Texture2D.h"
#include "Utilities.h"

const std::string dae::SpriteComponent::m_ComponentName{ "SpriteComponent" };

dae::SpriteComponent::SpriteComponent(const std::string& path)
	: m_Path{ path }, m_FlippedHorziontal(false), m_Width(-1), m_Height(-1), m_FramesPerSecond(1) {}

dae::SpriteComponent::SpriteComponent(const std::string& path, const int& clipWidth, const int& clipHeight)
	: m_Path{ path }, m_FlippedHorziontal(false), m_Width(clipWidth), m_Height(clipHeight), m_FramesPerSecond(1) {}

dae::SpriteComponent::SpriteComponent(const std::string& path, const int& clipWidth, const int& clipHeight, const float framesPerSec)
	: m_Path{ path }, m_FlippedHorziontal(false), m_Width(clipWidth), m_Height(clipHeight), m_FramesPerSecond(framesPerSec) {}

dae::SpriteComponent::~SpriteComponent()
{
	SAFE_DELETE(m_pTexture);
	for (std::pair<std::string, SpriteAnimation*> pSpriteAnim : m_pSpriteAnimations)
	{
		SAFE_DELETE(pSpriteAnim.second);
	}
}

void dae::SpriteComponent::Initialize()
{
	if (!m_Path.empty()) SetTexture(m_Path);
}

void dae::SpriteComponent::Update(float elapsed)
{
	m_AnimationElapsed += elapsed * m_FramesPerSecond;
}

void dae::SpriteComponent::Render()
{
	FRect src;
	src.width = static_cast<float>(m_Width);
	src.height = static_cast<float>(m_Height);

	//cutting the texture and animate if There is animation.
	if (m_CurrentSpriteAnimation)
	{
		src.left = src.width * ((int)m_AnimationElapsed % m_CurrentSpriteAnimation->frames);
		src.bottom = src.height * m_CurrentSpriteAnimation->column;
	}
	else
	{
		src.left = src.width;
		src.bottom = src.height;
	}

	//Placing of the texture
	const FRect dest = m_FlippedHorziontal ? FRect{ src.width,0,-src.width,src.height } : FRect{ 0,0,src.width,src.height };

	const auto position = m_pGameObject->GetTransform()->GetPosition();
	const auto scale = m_pGameObject->GetTransform()->GetScale();
	const auto rotation = m_pGameObject->GetTransform()->GetRotation();

	//Draw sprite with & applying transform position/scale/rotation
	glPushMatrix();
	glTranslatef(position.x, position.y, 0);
	glRotatef(rotation, 0, 0, 1);
	glScalef(scale, scale, 0);
	Renderer::GetInstance().RenderTexture2D(m_pTexture, dest, src);
	glPopMatrix();
}

const std::string dae::SpriteComponent::GetComponentName() const
{
	return m_ComponentName;
}

void dae::SpriteComponent::SetTexture(const std::string& filename)
{

	//If valid delete old one and replace by given new texture
	if (m_pTexture)
	{
		SAFE_DELETE(m_pTexture);

	}

	m_Path = filename;
	m_pTexture = ResourceManager::GetInstance().LoadImageTexture(filename);

	// Not defined size = default size
	if (m_Width == -1 || m_Height == -1)
	{
		m_Width = (int)m_pTexture->GetWidth();
		m_Height = (int)m_pTexture->GetHeight();
		return;
	}



}

void dae::SpriteComponent::FlipHorizontal()
{
	m_FlippedHorziontal = !m_FlippedHorziontal;
}

void dae::SpriteComponent::FlipHorizontal(bool enable)
{
	m_FlippedHorziontal = enable;
}

//Saves sprite animation with name, use PlayAnimation() to activate.
void dae::SpriteComponent::AddSpriteAnimation(SpriteAnimation* animation, const std::string name)
{
	if (!animation)
	{
		DEBUGLOG.PrintWarning("SpriteComponent::AddSpriteAnimation() SpriteAnimation == NULL");
		return;
	}

	for (std::pair<std::string, SpriteAnimation*> pSpriteAnim : m_pSpriteAnimations)
	{
		if (pSpriteAnim.first == name)
		{
			DEBUGLOG.PrintWarning("SpriteComponent::AddSpriteAnimation() animation name already used : " + name);
			SAFE_DELETE(animation);
			return;
		}

		if (pSpriteAnim.second == animation)
		{
			DEBUGLOG.PrintWarning("SpriteComponent::AddSpriteAnimation() animation is already added!");
			SAFE_DELETE(animation);
			return;
		}
	}

	m_pSpriteAnimations.insert(std::make_pair(name, animation));

}

void dae::SpriteComponent::RemoveSpriteAnimation(const std::string& name)
{
	const auto it = m_pSpriteAnimations.find(name);
	if (it == m_pSpriteAnimations.end())
	{
		DEBUGLOG.PrintWarning("SpriteComponent::RemoveSpriteAnimation() " + name + " not found!");
		return;
	}

	SAFE_DELETE(it->second);
	m_pSpriteAnimations.erase(it);
}

void dae::SpriteComponent::PlayAnimation(const std::string& name)
{
	//Extra optimilization for big animation list
	if (m_CurrentSpriteAnimationName == name) return;

	const auto it = m_pSpriteAnimations.find(name);
	if (it == m_pSpriteAnimations.end())
	{
		DEBUGLOG.PrintWarning("SpriteComponent::PlayAnimation() " + name + " not found!, Please use SpriteComponent::AddSpriteAnimation().");
		return;
	}

	m_CurrentSpriteAnimation = it->second;
	m_CurrentSpriteAnimationName = name;
}