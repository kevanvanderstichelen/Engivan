#pragma once
#include "Singleton.h"
#include "BoxColliderComponent.h"
namespace dae
{
	class WorldPhysics : public Singleton<WorldPhysics>
	{
	public:
		void Initialize();
		void Update(float elapsed);
		void AddCollider(BoxColliderComponent* collider) noexcept { m_pBoxColliders.push_back(collider); }
	private:
		friend class Singleton<WorldPhysics>;
		WorldPhysics() = default;
		std::vector<BoxColliderComponent*> m_pBoxColliders;

	};
}
