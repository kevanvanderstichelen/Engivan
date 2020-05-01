#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <SDL.h>
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Devlog.h"
#include "GameTime.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "AudioManager.h"

using namespace std;
using namespace dae;
using namespace std::chrono;

void dae::Engivan::Initialize(const std::string& wName, const int width, const int height)
{
	m_WindowWidth = width;
	m_WindowHeight = height;

	DEBUGLOG;

	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_pWindow = SDL_CreateWindow(
		wName.c_str(),
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		width,
		height,
		SDL_WINDOW_OPENGL
	);
	if (m_pWindow == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	m_Context = SDL_GL_CreateContext(m_pWindow);

	if (!m_Context)
	{
		throw std::runtime_error(std::string("SDL_GL_CreateContext Error: ") + SDL_GetError());
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, width, 0, height);

	glViewport(0, 0, int(width), int(height));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RENDERER.Initialize(m_pWindow);
	ResourceManager::GetInstance().Init("../Data/");
	GAME.Initialize();
	SCENEMANAGER.Initialize();
	TIME.Initialize();
	PHYSICS.Initialize();
}

void dae::Engivan::Cleanup()
{
	AudioManager::Reset();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_pWindow);
	m_pWindow = nullptr;
	SDL_GL_DeleteContext(m_Context);

	SDL_Quit();
}

void dae::Engivan::Run()
{
	{
		auto& input = InputManager::GetInstance();
		//double straggle = 0.0;

		while (input.ProcessInput()) //Input manager returns false when quit is pressed
		{
			TIME.Start();

			PHYSICS.Update(TIME.GetElapsed());

			SCENEMANAGER.Update(TIME.GetElapsed());



			////Catch up of delayed update
			//while (straggle >= (m_MsPerFrame / 1000.0) )
			//{
			//	SCENEMANAGER.Update(TIME.GetElapsed());
			//	straggle -= (m_MsPerFrame / 1000.0);
			//}

			//straggle += TIME.GetElapsed();
			RENDERER.Render();

			TIME.Stop();
		}
	}
}
