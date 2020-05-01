#include "MiniginPCH.h"

#if _DEBUG
#include <vld.h>
#endif

#include "Minigin.h"
#include "MainGame.h"
#include "SceneManager.h"
using namespace std;

int main(int, char*[]) 
{
	//Create all scenes
	ENGINE.Initialize("Enigvan", 640, 480);

	//Running the game
	ENGINE.Run();

	//OpenGL & SDL Cleanup & Dynamically allocated memory.
	ENGINE.Cleanup();

    return 0;
}
