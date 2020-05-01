#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include <string>
#include "BaseComponent.h"
#include <map>

namespace dae
{
	struct SpriteAnimation
	{
	public:

		SpriteAnimation(const uint& frames, int column) : frames(frames), column(column) {}
		uint frames{};
		int column{};
	};

	class Texture2D;
	class SpriteComponent final : public BaseComponent
	{
	public:
		SpriteComponent(const std::string& path);
		SpriteComponent(const std::string& path, const int& clipWidth, const int& clipHeight);
		SpriteComponent(const std::string& path, const int& clipWidth, const int& clipHeight, const float framesPerSec);

		virtual ~SpriteComponent();
		SpriteComponent(const SpriteComponent& other) = delete;
		SpriteComponent(SpriteComponent&& other) noexcept = delete;
		SpriteComponent& operator=(const SpriteComponent& other) = delete;
		SpriteComponent& operator=(SpriteComponent&& other) noexcept = delete;

		virtual void Initialize();
		virtual void Update(float elapsed);
		virtual void Render();
		virtual const std::string GetComponentName() const;

		void AddSpriteAnimation(SpriteAnimation* animation, const std::string name);
		void RemoveSpriteAnimation(const std::string& name);
		void PlayAnimation(const std::string& name);

		void FlipHorizontal();
		void FlipHorizontal(bool enable);

		void SetTexture(const std::string& filename);

		const Texture2D* GetTexture() const noexcept { return m_pTexture; };
		const int GetWidth() const noexcept { return m_Width; }
		const int GetHeight() const noexcept { return m_Height; }
		const std::string& GetCurrentSpriteName() const noexcept { return m_CurrentSpriteAnimationName; }
		const SpriteAnimation* GetCurrentSpriteAnimation() const noexcept { return m_CurrentSpriteAnimation; }


	private:
		static const std::string m_ComponentName;
		Texture2D* m_pTexture{};
		std::string m_Path;
		bool m_FlippedHorziontal = false;
		int m_Width, m_Height;
		float m_AnimationElapsed;
		const float m_FramesPerSecond;
		SpriteAnimation* m_CurrentSpriteAnimation;
		std::string m_CurrentSpriteAnimationName;
		std::map<std::string, SpriteAnimation*> m_pSpriteAnimations;
	};


}
