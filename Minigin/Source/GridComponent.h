#pragma once
#include "BaseComponent.h"
#include <string>

namespace dae
{
	class GridComponent final : public BaseComponent
	{
	public:
		GridComponent();
		GridComponent(const FPoint2& position, const int width, const int height);

		virtual ~GridComponent() = default;
		GridComponent(const GridComponent& other) = delete;
		GridComponent(GridComponent&& other) noexcept = delete;
		GridComponent& operator=(const GridComponent& other) = delete;
		GridComponent& operator=(GridComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		void AddEffectingObject(GameObject* object) noexcept { m_pGameObjects.push_back(object); };

	private:
		static const std::string m_ComponentName;
		const int m_Width, m_Height;
		const FPoint2 m_Position;
		std::vector<GameObject*> m_pGameObjects;
	};

}
