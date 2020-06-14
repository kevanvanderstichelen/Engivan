#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameTime.h"
#include "InputManager.h"
#include "Utilities.h"
#include <algorithm>
#include "Devlog.h"

dae::SceneManager::~SceneManager()
{
	for (auto& scene : m_pScenes)
	{
		SAFE_DELETE(scene);
	}
}

void dae::SceneManager::AddScene(Scene* scene)
{
	m_pScenes.push_back(scene);
	m_pCurrentScene = scene;
}

void dae::SceneManager::Initialize()
{
	for (auto scene : m_pScenes)
	{
		scene->RootInitialize();
	}
}

void dae::SceneManager::Update(float elapsed)
{
	GameTime::GetInstance().Update(elapsed);
	InputManager::GetInstance().Update(elapsed);

	m_pCurrentScene->RootUpdate(elapsed);
}

void dae::SceneManager::Render()
{
	m_pCurrentScene->RootRender();
}

void dae::SceneManager::SetActiveScene(const std::string& name)
{
	auto it = std::find_if(m_pScenes.begin(), m_pScenes.end(), [name](Scene* scene)
		{
			return scene->m_Name == name ? true : false;
		});

	if (it != m_pScenes.end())
	{
		m_pCurrentScene = *it;
	}
	else
	{
		Devlog::GetInstance().PrintWarning("SceneManager::SetActiveScene() No active scene found with name: " + name);
	}
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_pCurrentScene;
}

dae::Scene* dae::SceneManager::GetPtrActiveScene()
{
	return m_pCurrentScene;
}
