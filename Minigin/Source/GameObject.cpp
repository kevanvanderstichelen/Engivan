#pragma once
#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Utilities.h"
#include "Devlog.h"
#include "BaseComponent.h"
#include "TransformComponent.h"

dae::GameObject::GameObject()
	:m_Tag(""), m_pParent(this)
{
	m_pTransform = new dae::TransformComponent();
	m_pComponents.push_back(m_pTransform);
}

dae::GameObject::~GameObject()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		SAFE_DELETE(pComponent);
	}

	for (auto pChild : m_pChilderens)
	{
		SAFE_DELETE(pChild);
	}
};

void dae::GameObject::RootInitialize()
{
	Initialize();
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Initialize();
	}

	for (auto pChild : m_pChilderens)
	{
		pChild->RootInitialize();
	}

	m_IsInitialized = true;
}

void dae::GameObject::RootUpdate(float elapsed)
{ 
	if (!m_IsActive || !m_IsInitialized) return;
	Update(elapsed);
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Update(elapsed);
	}

	for (auto pChild : m_pChilderens)
	{
		pChild->RootUpdate(elapsed);
	}


}

void dae::GameObject::RootRender() const
{
	if (!m_IsActive || !m_IsInitialized) return;

	Render();
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Render();
	}

	for (auto pChild : m_pChilderens)
	{
		pChild->RootRender();
	}

}

void dae::GameObject::AddComponent(dae::BaseComponent* component)
{
	//Check duplicate component
	for (BaseComponent* pComponent : m_pComponents)
	{
		if (typeid(*component) == typeid(pComponent))
		{
			Devlog::GetInstance().PrintWarning("GameObject::AddComponent - " + component->GetComponentName() + " already exist!");
			return;
		}
	}

	m_pComponents.push_back(component);
	component->m_pGameObject = this;
}

void dae::GameObject::RemoveComponent(dae::BaseComponent* component)
{
	auto iterator = std::find(m_pComponents.begin(), m_pComponents.end(), component);

	if (iterator == m_pComponents.end())
	{
		Devlog::GetInstance().PrintWarning("GameObject::RemoveComponent - " + component->GetComponentName() + " does not exist!");
		return;
	}

	m_pComponents.erase(iterator);
}

dae::TransformComponent* dae::GameObject::GetTransform()
{
	return m_pTransform;
}

void dae::GameObject::AddChild(GameObject* object)
{
	if (object)
	{
		object->m_pParent = this;
		object->RootInitialize();
		m_pChilderens.push_back(object);
	}

}

void dae::GameObject::RemoveChild(GameObject* object)
{
	if (object)
	{
		auto it = std::find(m_pChilderens.begin(), m_pChilderens.end(), object);
		m_pChilderens.erase(it);
		SAFE_DELETE(object);
	}

}
