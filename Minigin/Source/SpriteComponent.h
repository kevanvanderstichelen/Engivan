#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include <string>
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent();

		virtual ~SpriteComponent() = default;
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		void SetTexture(const std::string& filename);
	private:
		static const std::string m_ComponentName;
		std::shared_ptr<Texture2D> m_Texture{};
	};


}
