#include "MiniginPCH.h"
#include "GameTime.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "TextComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::GameTime::GameTime()
	:m_FPS{ 0 }, m_ElapsedFPS{ 0 }, m_FPSframes { 0 }, m_Elapsed { 0 }, m_pFpsText{ nullptr }
	, m_Transform{ {5,5,0} }, m_Color{ 255, 255, 0, 255 }, m_FontScale{ 18 }
{
}

dae::GameTime::GameTime(const Transform& transform, const SDL_Color& fColor, const int fScale)
	:m_FPS{ 0 }, m_ElapsedFPS{ 0 }, m_FPSframes{ 0 }, m_Elapsed{ 0 }, m_pFpsText{ nullptr }
	,m_Transform{ transform }, m_Color{ fColor }, m_FontScale{ fScale }
{
}

void dae::GameTime::Initialize()
{
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", m_FontScale);
	
	m_pFpsText = std::make_shared<GameObject>();
	m_pFpsText->AddComponent(new TextComponent("0 FPS", font, m_Color));
	m_pFpsText->GetTransformComponent()->SetPosition(m_Transform.GetPosition());
	SceneManager::GetInstance().GetActiveScene().Add(m_pFpsText);
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
		m_pFpsText->GetComponent<TextComponent>()->SetText(std::to_string((int)m_FPS) + " FPS");
		m_FPSframes = 0;
	}

}


void dae::GameTime::Render() const
{
	
}

