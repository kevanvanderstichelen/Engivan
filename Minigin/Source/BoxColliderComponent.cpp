#include "MiniginPCH.h"
#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "Texture2D.h"
#include "RigidBodyComponent.h"

dae::BoxColliderComponent::BoxColliderComponent(const bool isStatic, const bool isTrigger)
	: m_Rectangle(0,0,1,1), m_IsStatic(isStatic), m_IsTrigger(isTrigger)
	, m_CollisionCallBack(nullptr), m_TriggerCallBack(nullptr)
	, m_Penetrate(0,0)

{
}
void dae::BoxColliderComponent::Initialize()
{
	float width = m_Rectangle.width;
	float height = m_Rectangle.height;
	FPoint2 position(0, 0);
	FVector3 pivot(0, 0, 0);
	
	if (!m_pGameObject) return;

	const auto sprite = m_pGameObject->GetComponent<SpriteComponent>();
	if (!sprite)
	{
		DEBUGLOG.PrintWarning("BoxColliderComponent::BoxColliderComponent() No spritecomponent attached, using default width/height of collider");
	}
	else
	{
		width = (float)sprite->GetWidth();
		height = (float)sprite->GetHeight();
	}

	const auto transform = m_pGameObject->GetTransform();
	if (!transform)
		DEBUGLOG.PrintWarning("BoxColliderComponent::BoxColliderComponent() No transform component attached, using default value: 0,0 as position @ constructor");
	else
	{
		position = transform->GetPosition2D();
		width *= transform->GetScale();
		height *= transform->GetScale();
	}

	m_Rectangle.left = position.x;
	m_Rectangle.bottom = position.y;
	m_Rectangle.width = width ;
	m_Rectangle.height = height ;


	PHYSICS.AddCollider(this);
}

void dae::BoxColliderComponent::Update(float)
{
	if (m_IsStatic) return;

	m_Rectangle.left = m_pGameObject->GetTransform()->GetPosition().x;
	m_Rectangle.bottom = m_pGameObject->GetTransform()->GetPosition().y;

}

void dae::BoxColliderComponent::Render()
{
#ifdef _DEBUG
	RENDERER.DrawRect(m_Rectangle, 1.f);
#endif
}

const std::string dae::BoxColliderComponent::GetComponentName() const
{
	return std::string();
}

void dae::BoxColliderComponent::OnCollisionEnter(const BoxColliderComponent* other)
{
	if (m_IsTrigger)
	{
		if (m_TriggerCallBack) m_TriggerCallBack(m_pGameObject, other->m_pGameObject);
		return;
	}

	auto rigidBody = m_pGameObject->GetComponent<RigidBodyComponent>();

	const FRect& otherBox = other->GetRectBounds();

	const float vX = (m_Rectangle.left + (m_Rectangle.width / 2)) - (otherBox.left + (otherBox.width / 2));
	const float vY = (m_Rectangle.bottom + (m_Rectangle.height / 2)) - (otherBox.bottom + (otherBox.height / 2));
	const float totWidth = (m_Rectangle.width / 2) + (otherBox.width / 2);
	const float totHeight = (m_Rectangle.height / 2) + (otherBox.height / 2);

	//Check overlapping -> Resolve translation on collider & transform.
	if (abs(vX) < totWidth && abs(vY) < totHeight)
	{
		float oX = totWidth - abs(vX);
		float oY = totHeight - abs(vY);

		if (oX >= oY) 
		{
			//TOP & BOTTOM
			m_Penetrate.y = oY = (vY > 0) ? oY : -oY;
			m_pGameObject->GetTransform()->TranslateY(oY);
			m_Rectangle.bottom += oY;
			if (rigidBody) rigidBody->m_LinearVelocity.y = 0;
		}
		else 
		{
			//LEFT & RIGHT
			m_Penetrate.x = oX = (vX > 0) ? oX : -oX;
			m_pGameObject->GetTransform()->TranslateX(oX);
			m_Rectangle.left += oX;
			if (rigidBody) rigidBody->m_LinearVelocity.x = 0;
		}
	}

	if (m_CollisionCallBack) m_CollisionCallBack(m_pGameObject, other->m_pGameObject);
}

const bool dae::BoxColliderComponent::IsOverlapping(const BoxColliderComponent* other)
{
	const FRect& otherBox = other->GetRectBounds();
	if (m_Rectangle.left + m_Rectangle.width >= (otherBox.left) &&
		m_Rectangle.left <= (otherBox.left + otherBox.width) &&
		m_Rectangle.bottom + m_Rectangle.height >= otherBox.bottom &&
		m_Rectangle.bottom <= (otherBox.bottom + otherBox.height))
	{
		return true;
	}
	else
	{
		m_Penetrate.x = m_Penetrate.y = 0;
		return false;
	}
}


