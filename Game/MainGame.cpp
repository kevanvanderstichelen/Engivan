#pragma once
#include "MainGame.h"
#include "BubbleBobbleScene.h"

namespace dae
{
	void MainGame::Initialize()
	{
		SCENEMANAGER.AddScene(new BubbleBobbleScene());
	}

}
