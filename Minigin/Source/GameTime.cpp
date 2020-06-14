#include "MiniginPCH.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Scene.h"

#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"


dae::GameTime::GameTime()
	:m_FPS{ 0 }, m_ElapsedFPS{ 0 }, m_FPSframes { 0 }, m_Elapsed { 0 }
{
}

void dae::GameTime::Initialize()
{

}

void dae::GameTime::AddFPSCounter(Scene& scene)
{
	GameObject* fpsCounter = new GameObject();
	fpsCounter->AddComponent(new FPSComponent());
	fpsCounter->GetTransform()->Translate(5, (float)ENGINE.GetWindowHeight() - 15, 0);
	scene.Add(fpsCounter);
}

dae::GameTime::~GameTime()
{
}

void dae::GameTime::Start()
{
	m_BeginElapsed = std::chrono::high_resolution_clock::now();
}

void dae::GameTime::Stop()
{
	m_EndElapsed = std::chrono::high_resolution_clock::now();
	m_Elapsed = std::chrono::duration_cast<std::chrono::duration<float>>(m_EndElapsed - m_BeginElapsed);
}

void dae::GameTime::Update(float)
{
	m_ElapsedFPS += (float)m_Elapsed.count();
	++m_FPSframes;

	if (m_ElapsedFPS >= 1.0f)
	{
		m_ElapsedFPS -= m_ElapsedFPS;
		m_FPS = m_FPSframes;
		m_FPSframes = 0;
	}

}


void dae::GameTime::Render() const
{

}

