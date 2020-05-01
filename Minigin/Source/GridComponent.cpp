#include "MiniginPCH.h"
#include "GridComponent.h"
#include "TransformComponent.h"

dae::GridComponent::GridComponent()
	:m_Position(FPoint2(0,0)), m_Width(ENGINE.GetWindowWidth()), m_Height(ENGINE.GetWindowHeight()) { }

dae::GridComponent::GridComponent(const FPoint2& position, const int width, const int height)
	:m_Position(position), m_Width(width), m_Height(height) { }

void dae::GridComponent::Initialize()
{
}

void dae::GridComponent::Update(float )
{
	for (GameObject* object : m_pGameObjects)
	{
		const FPoint2& position = object->GetTransform()->GetPosition2D();

		if (position.y < m_Position.y)
		{
			object->GetTransform()->SetPosition(position.x, m_Position.y + m_Height);
			continue;
		}
		if (position.y > m_Position.y + m_Height)
		{
			object->GetTransform()->SetPosition(position.x, m_Position.y);
			continue;
		}
		if (position.x > m_Position.x + m_Width)
		{
			object->GetTransform()->SetPosition(m_Position.x, position.y);
			continue;
		}
		if (position.x < m_Position.x)
		{
			object->GetTransform()->SetPosition(m_Position.x + m_Width, position.y);
			continue;
		}
	}
}

void dae::GridComponent::Render()
{
}

const std::string dae::GridComponent::GetComponentName() const
{
	return m_ComponentName;
}
