#include "MiniginPCH.h"

#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#include <vld.h>
#endif

#include "SDL.h"
#include "Minigin.h"
using namespace std;
int main(int, char*[]) {

	dae::Engivan engine;
	engine.Run();
    return 0;
}
