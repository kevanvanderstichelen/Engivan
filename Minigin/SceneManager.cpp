#include "MiniginPCH.h"
#include "SceneManager.h"
#include "Scene.h"
#include "GameTime.h"

void dae::SceneManager::Update(float elapsed)
{
	for(auto& scene : m_Scenes)
	{
		scene->Update(elapsed);
	}
	GameTime::GetInstance().Update(elapsed);
}

void dae::SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		scene->Render();
	}
}

dae::Scene& dae::SceneManager::GetActiveScene()
{
	return *m_pCurrentScene;
}

dae::Scene& dae::SceneManager::CreateScene(const std::string& name)
{
	m_pCurrentScene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(m_pCurrentScene);
	return *m_pCurrentScene;
}
