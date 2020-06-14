#include "MiniginPCH.h"
#include "WorldPhysics.h"
#include "GameObject.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

void dae::WorldPhysics::Initialize()
{
}

void dae::WorldPhysics::Update(float)
{
	for (BoxColliderComponent* collider : m_pBoxColliders)
	{
		for (BoxColliderComponent* Othercollider : m_pBoxColliders)
		{
			if (collider == Othercollider) continue;

			if (collider->IsOverlapping(Othercollider))
			{
				collider->OnCollisionEnter(Othercollider);
			}
		}
	}

}

void dae::WorldPhysics::RemoveCollider(BoxColliderComponent* collider)
{
	auto iterator = std::find(m_pBoxColliders.begin(), m_pBoxColliders.end(), collider);

	if (iterator == m_pBoxColliders.end())
	{
		return;
	}

	m_pBoxColliders.erase(iterator);

}
