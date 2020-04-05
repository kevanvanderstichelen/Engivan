#pragma once
#include "Singleton.h"

namespace dae
{
	class WorldPhysics : public Singleton<WorldPhysics>
	{
	public:
		void Initialize();
		void Update(float elapsed);
	private:
		friend class Singleton<WorldPhysics>;
		WorldPhysics() = default;

	};
}
