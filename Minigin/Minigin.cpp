#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include <thread>
#include <SDL.h>
#include "TextComponent.h"
#include "GameObject.h"
#include "Scene.h"
#include "Devlog.h"
#include "GameTime.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

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

/**
 * Code constructing the scene world starts here
 */
void dae::Engivan::LoadGame()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	auto go = std::make_shared<GameObject>();
	go->AddComponent(new SpriteComponent());
	go->GetComponent<SpriteComponent>()->SetTexture("background.jpg");
	scene.Add(go);

	go = std::make_shared<GameObject>();
	go->AddComponent(new SpriteComponent());
	go->GetComponent<SpriteComponent>()->SetTexture("logo.png");
	go->GetComponent<TransformComponent>()->SetPosition(216, 180);
	scene.Add(go);

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 32);

	go = std::make_shared<GameObject>();
	go->AddComponent(new TextComponent("Programming 4 Assignment", font));
	go->GetComponent<TransformComponent>()->SetPosition(110, 20);
	scene.Add(go);
}

void dae::Engivan::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Engivan::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

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

			doContinue = input.ProcessInput();
			sceneManager.Update(gameTime.GetElapsed());


			straggle += gameTime.GetElapsed();

			while (straggle >= (m_MsPerFrame / 1000.0) )
			{
				sceneManager.Update(gameTime.GetElapsed());
				straggle -= (m_MsPerFrame / 1000.0);
			}

			renderer.Render();

			gameTime.Stop();
		}
	}

	Cleanup();
}
