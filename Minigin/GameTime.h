#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Singleton.h"
#include <chrono>
#include <SDL.h>
#include "Transform.h" 


namespace dae
{
	class GameObject;
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime();
		GameTime(const Transform& transform, const SDL_Color& fColor, const int fScale);
		~GameTime();

		GameTime(const GameTime& other) = delete;
		GameTime(GameTime&& other) noexcept = delete;
		GameTime& operator=(const GameTime& other) = delete;
		GameTime& operator=(GameTime&& other) noexcept = delete;


		void Start();
		void Stop();
		void Update(float elapsed);
		void Render() const;
		void Initialize();


		const float GetElapsed() const { return static_cast<float>(m_Elapsed.count()); }
		const int GetFPS() const { return m_FPS; }

	protected:
	private:
		std::chrono::duration<float> m_Elapsed;
		std::chrono::time_point<std::chrono::steady_clock> m_BeginElapsed;
		std::chrono::time_point<std::chrono::steady_clock> m_EndElapsed;
		int m_FPS;
		float m_ElapsedFPS;
		int m_FPSframes;
		int m_FontScale;
		std::shared_ptr<GameObject> m_pFpsText;
		Transform m_Transform;
		SDL_Color m_Color;
	};
}


