#pragma once
#include "GameObject.h"
namespace dae
{
	class BaseComponent
	{
		friend class GameObject;
	public:
		BaseComponent();
		virtual ~BaseComponent() = default;
		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) noexcept = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) noexcept = delete;

		virtual void Initialize() = 0;
		virtual void Update(float elapsed) = 0;
		virtual void Render() = 0;
		virtual const std::string GetComponentName() const = 0;
	protected:

		GameObject* m_pGameObject;
	};
}


