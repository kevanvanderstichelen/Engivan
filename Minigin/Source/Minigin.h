#pragma once

struct SDL_Window;
namespace dae
{
	class TextObject;
	class Engivan : public Singleton<Engivan>
	{
	public:

		void Initialize(const std::string& wName, const int width, const int height);
		void Cleanup();
		void Run();

		const int GetWindowWidth() const { return m_WindowWidth; }
		const int GetWindowHeight() const { return m_WindowHeight; }

	private:
		static const int m_MsPerFrame = 8; //16 for 60 fps, 33 for 30 fps
		int m_WindowWidth;
		int m_WindowHeight;
		SDL_Window* m_pWindow{};
		SDL_GLContext m_Context;
	};
}