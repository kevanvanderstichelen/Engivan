#include "MiniginPCH.h"
#include "GridComponent.h"
#include "TransformComponent.h"
#include "Scene.h"
#include "CameraComponent.h"

const std::string dae::GridComponent::m_ComponentName{ "GridComponent" };

dae::GridComponent::GridComponent()
	:m_Position(FPoint2(0,0)), m_Width(ENGINE.GetWindowWidth()), m_Height(ENGINE.GetWindowHeight()) { }

dae::GridComponent::GridComponent(const FPoint2& position, const int width, const int height)
	:m_Position(position), m_Width(width), m_Height(height) { }

void dae::GridComponent::Initialize()
{
	const auto& box = m_pGameObject->GetComponent<BoxColliderComponent>();
	
	//Get the middle of the object (more realistic clipping)
	if (box)
	{
		const FRect& rect = box->GetRectBounds();
		m_Position.x -= rect.width / 2;
		m_Position.y -= rect.height / 2;
	}

}

void dae::GridComponent::Update(float )
{
	const FPoint2& position = m_pGameObject->GetTransform()->GetPosition2D();
	const FPoint2& cameraPos = SCENEMANAGER.GetActiveScene().GetActiveCamera()->GetPosition();

	if (position.y < m_Position.y + cameraPos.y)
	{
		m_pGameObject->GetTransform()->SetPosition(position.x, m_Position.y + m_Height + cameraPos.y);
	}
	if (position.y > m_Position.y + m_Height + cameraPos.y)
	{
		m_pGameObject->GetTransform()->SetPosition(position.x, m_Position.y + cameraPos.y);

	}
	if (position.x > m_Position.x + m_Width + cameraPos.x)
	{
		m_pGameObject->GetTransform()->SetPosition(m_Position.x + cameraPos.x, position.y);

	}
	if (position.x < m_Position.x + cameraPos.x)
	{
		m_pGameObject->GetTransform()->SetPosition(m_Position.x + m_Width + cameraPos.x, position.y);
	}
}

void dae::GridComponent::Render()
{
}

const std::string dae::GridComponent::GetComponentName() const
{
	return m_ComponentName;
}
