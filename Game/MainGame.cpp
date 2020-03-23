#pragma once
#include "MainGame.h"
#include "BubbleBobbleScene.h"

namespace dae
{
	void MainGame::Initialize()
	{
		 SceneManager::GetInstance().AddScene(new BubbleBobbleScene());
	}

}
