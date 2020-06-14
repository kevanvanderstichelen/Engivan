#pragma once

#pragma warning(push)
#pragma warning (disable:4201)
#include <glm/vec3.hpp>
#pragma warning(pop)

#include "Singleton.h"
#include <chrono>
#include <SDL.h>

#include "SceneManager.h"

namespace dae
{
	class GameObject;
	class FPSComponent;
	class GameTime final : public Singleton<GameTime>
	{
	public:
		GameTime();
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

		void AddFPSCounter(Scene& scene = SceneManager::GetInstance().GetActiveScene());

		const float GetElapsed() const { return static_cast<float>(m_Elapsed.count()); }
		const int GetFPS() const { return m_FPS; }

	protected:
	private:
		friend class FPSComponent;
		std::chrono::duration<float> m_Elapsed;
		std::chrono::time_point<std::chrono::steady_clock> m_BeginElapsed;
		std::chrono::time_point<std::chrono::steady_clock> m_EndElapsed;
		int m_FPS;
		float m_ElapsedFPS;
		int m_FPSframes;
		float m_FPSCounterPosX, m_FPSCounterPosY;

	};
}


