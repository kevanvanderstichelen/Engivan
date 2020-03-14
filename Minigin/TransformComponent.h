#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "BaseComponent.h"

namespace dae
{
	class TransformComponent final : public BaseComponent
	{
	public:

		TransformComponent();
		TransformComponent(const glm::vec3& position);
		TransformComponent(const glm::vec3& position, const float rotation);
		TransformComponent(const glm::vec3& position, const float rotation, const float scale);

		virtual ~TransformComponent() = default;
		TransformComponent(const TransformComponent& other) = delete;
		TransformComponent(TransformComponent&& other) noexcept = delete;
		TransformComponent& operator=(const TransformComponent& other) = delete;
		TransformComponent& operator=(TransformComponent&& other) noexcept = delete;

		void SetPosition(const float x, const float y);
		void SetPosition(const float x, const float y, const float z);
		void SetPosition(const glm::vec3& position);
		void SetScale(const float scale);
		void SetRotation(const float rotation);

		virtual const std::string GetComponentName() const;

		const glm::vec3 GetPosition() const;
		const float GetScale() const;
		const float GetRotation() const;

		void Initialize() override;
		void Update(float elapsed) override;
		void Render() override;

	private:
		static const std::string m_ComponentName;
		glm::vec3 m_Position;
		float m_Scale;
		float m_Rotation;
	};

}


