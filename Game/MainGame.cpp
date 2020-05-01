#pragma once
#include "MainGame.h"
#include "BubbleBobbleScene.h"
#include "StartScene.h"

namespace dae
{
	void MainGame::Initialize()
	{
		SCENEMANAGER.AddScene(new BubbleBobbleScene());
		SCENEMANAGER.AddScene(new StartScene());
	}

}
