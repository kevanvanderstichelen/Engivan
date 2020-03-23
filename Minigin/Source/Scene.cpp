#include "MiniginPCH.h"
#include "Scene.h"
#include "Utilities.h"
#include "GameObject.h"
#include "Devlog.h"

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene()
{
	for (auto& object : m_pGameObjects)
	{
		SAFE_DELETE(object);
	}
};

void Scene::Add(GameObject* object)
{
	m_pGameObjects.push_back(object);
}

void Scene::Remove(GameObject* object)
{
	auto it = std::find(m_pGameObjects.begin(), m_pGameObjects.end(), object);
	if (it == m_pGameObjects.end())
	{
		Devlog::GetInstance().PrintWarning("Scene::Remove() Game object not found/valid!");
		return;
	}
	m_pGameObjects.erase(it);
	object = nullptr;
}

void dae::Scene::RootInitialize()
{
	Initialize();
}

void dae::Scene::RootUpdate(float elapsed)
{
	for (auto& object : m_pGameObjects)
	{
		object->Update(elapsed);
	}
	Update(elapsed);
}

void dae::Scene::RootRender() const
{
	for (const auto& object : m_pGameObjects)
	{
		object->Render();
	}
	Render();
}