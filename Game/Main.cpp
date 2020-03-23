#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif


#include <SDL.h>
#include <SDL_mixer.h>

#include "Minigin.h"
#include "MainGame.h"
#include "SceneManager.h"
using namespace std;

int main(int, char*[]) 
{
	dae::Engivan engine;
	dae::MainGame game;

	//Create all scenes
	engine.Initialize();
	game.Initialize();

	//Initialize all scenes
	dae::SceneManager::GetInstance().Initialize();

	//Running the game
	engine.Run();

	engine.Cleanup();

    return 0;
}
