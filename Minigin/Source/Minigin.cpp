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

void dae::Engivan::Initialize()
{
	Devlog::GetInstance();
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Engivan - Kevan Vanderstichelen",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

void dae::Engivan::Cleanup()
{
	AudioManager::Reset();
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
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
