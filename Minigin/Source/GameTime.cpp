#include "MiniginPCH.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "FPSComponent.h"


dae::GameTime::GameTime()
	:m_FPS{ 0 }, m_ElapsedFPS{ 0 }, m_FPSframes { 0 }, m_Elapsed { 0 }, m_pFPSObject{ nullptr }, m_FPSCounter{ false }
{
}

void dae::GameTime::Initialize()
{
	if (m_FPSCounter)
	{
		m_pFPSObject = new GameObject;
		m_pFPSObject->AddComponent(new FPSComponent());
		m_pFPSObject->GetComponent<FPSComponent>()->Initialize();
		m_pFPSObject->GetTransform()->SetPosition(0, (float)ENGINE.GetWindowHeight() - 18.f, 0.1f);
	}
}

void dae::GameTime::ScreenFPSCounter(bool enable)
{
	m_FPSCounter = enable;
}

dae::GameTime::~GameTime()
{
	SAFE_DELETE(m_pFPSObject);
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

void dae::GameTime::Update(float elapsed)
{
	m_ElapsedFPS += (float)m_Elapsed.count();
	++m_FPSframes;

	if (m_ElapsedFPS >= 1.0f)
	{
		m_ElapsedFPS -= m_ElapsedFPS;
		m_FPS = m_FPSframes;
		m_FPSframes = 0;
	}

	if (m_pFPSObject) m_pFPSObject->Update(elapsed);
}


void dae::GameTime::Render() const
{
	if (m_pFPSObject) m_pFPSObject->Render();

}

