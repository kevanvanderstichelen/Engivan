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
};

void dae::GameObject::Initialize()
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Initialize();
	}
}

void dae::GameObject::Update(float elapsed)
{ 
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Update(elapsed);
	}
}

void dae::GameObject::Render() const
{
	for (BaseComponent* pComponent : m_pComponents)
	{
		pComponent->Render();
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
	auto iterator = find(m_pComponents.begin(), m_pComponents.end(), component);

	if (iterator == m_pComponents.end())
	{
		Devlog::GetInstance().PrintWarning("GameObject::RemoveComponent - " + component->GetComponentName() + " does not exist!");
		return;
	}

	m_pComponents.erase(iterator);
}

dae::TransformComponent* dae::GameObject::GetTransformComponent()
{
	return m_pTransform;
}
