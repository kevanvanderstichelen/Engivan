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

	SAFE_DELETE(m_pCameraComponent);
};

void Scene::Add(GameObject* object)
{
	object->SetLinkedScene(this);
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
	SAFE_DELETE(object);
	object = nullptr;
}

void dae::Scene::SetActiveCamera(CameraComponent* pCamera)
{
	if (pCamera)
	{
		if (m_pCameraComponent) SAFE_DELETE(m_pCameraComponent);
		m_pCameraComponent = pCamera;
	}
	else
	{
		Devlog::GetInstance().PrintWarning("Scene::SetActiveCamera() assigned parameter is nullptr!");
	}
}

void dae::Scene::RootInitialize()
{
	m_pCameraComponent = new CameraComponent();

	Initialize();
	for (auto& object : m_pGameObjects)
	{
		object->RootInitialize();
	}

	if (m_pCameraComponent)
	{
		m_pCameraComponent->Initialize();
	}
}

void dae::Scene::RootUpdate(float elapsed)
{
	for (auto& object : m_pGameObjects)
	{
		object->RootUpdate(elapsed);
	}
	Update(elapsed);

	if (m_pCameraComponent)
	{
		m_pCameraComponent->Update(elapsed);
	}
}

void dae::Scene::RootRender() const
{
	m_pCameraComponent->Begin();
	for (const auto& object : m_pGameObjects)
	{
		object->RootRender();
	}
	Render();

	m_pCameraComponent->End();



	if (m_pCameraComponent)
	{
		m_pCameraComponent->Render();
	}


}