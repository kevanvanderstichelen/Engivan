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
