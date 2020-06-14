#include "MiniginPCH.h"
#include "CameraComponent.h"
#include "Utilities.h"
#include "TransformComponent.h"


dae::CameraComponent::CameraComponent()
	:m_Position{0,0}, m_Width(ENGINE.GetWindowWidth()), m_Height(ENGINE.GetWindowHeight())
{
}

dae::CameraComponent::CameraComponent(const FPoint2& position, const int width, const int height)
	: m_Position{ position }, m_Width(width), m_Height(height)
{
}

dae::CameraComponent::~CameraComponent()
{
	for (auto obj : m_pScreenObjects)
	{
		SAFE_DELETE(obj);
	}
}

void dae::CameraComponent::Initialize()
{
	for (auto obj : m_pScreenObjects)
	{
		obj->RootInitialize();
	}
}

void dae::CameraComponent::Update(float elapsed)
{
	for (auto obj : m_pScreenObjects)
	{
		obj->GetTransform()->SetPosition(m_Position.x, m_Position.y);
		obj->RootUpdate(elapsed);
	}
}

void dae::CameraComponent::Render()
{
	for (auto obj : m_pScreenObjects)
	{
		obj->RootRender();
	}
}

const std::string dae::CameraComponent::GetComponentName() const
{
	return std::string();

}

void dae::CameraComponent::SetPosition(const FVector2& pos)
{
	m_Position.x = pos.x;
	m_Position.y = pos.y;
}

void dae::CameraComponent::Translate(const FVector2& pos)
{
	m_Position.x += pos.x;
	m_Position.y += pos.y;
}

void dae::CameraComponent::AddToScreen(GameObject* gameObject)
{
	m_pScreenObjects.push_back(gameObject);
}

void dae::CameraComponent::Begin()
{
	glPushMatrix();
	glTranslatef(-m_Position.x, -m_Position.y, 0);
}

void dae::CameraComponent::End()
{
	glPopMatrix();
}
