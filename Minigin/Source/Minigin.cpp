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

	Renderer::GetInstance().Init(m_pWindow);
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

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();
		auto& gameTime = GameTime::GetInstance();

		gameTime.Initialize();

		bool doContinue = true;
		double straggle = 0.0;

		while (doContinue)
		{
			gameTime.Start();

			//Input manager returns false when quit is pressed
			doContinue = input.ProcessInput();

			sceneManager.Update(gameTime.GetElapsed());

			straggle += gameTime.GetElapsed();

			//Catch up of delayed update
			while (straggle >= (m_MsPerFrame / 1000.0) )
			{
				sceneManager.Update(gameTime.GetElapsed());
				straggle -= (m_MsPerFrame / 1000.0);
			}

			renderer.Render();
			gameTime.Stop();
		}
	}
}
