#include "MiniginPCH.h"
#include "UIComponent.h"
#include "ResourceManager.h"
#include "TransformComponent.h"
#include "TextComponent.h"
#include "Scene.h"
#include "Colors.h"

dae::UIComponent::UIComponent()
{
}

void dae::UIComponent::Initialize()
{
	const auto& windowWidth = ENGINE.GetWindowWidth();
	const auto& windowHeight = ENGINE.GetWindowHeight();
	const auto& font18 = ResourceManager::GetInstance().LoadFont("../Game/Resources/Font/BubbleBobbleFont.ttf", 18);

	//STATIC TEXT's
	m_pPlayer1Text = new GameObject();
	m_pPlayer1Text->AddComponent(new TransformComponent());
	m_pPlayer1Text->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 5, windowHeight - 20.f, 0));
	m_pPlayer1Text->AddComponent(new TextComponent("1UP", font18, TextAllignment::Middle));
	m_pPlayer1Text->GetComponent<TextComponent>()->SetColor(dae::Colors::Green);
	SCENEMANAGER.GetActiveScene().Add(m_pPlayer1Text);


	m_pTotalText = new GameObject();
	m_pTotalText->AddComponent(new TransformComponent());
	m_pTotalText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 20.f, 0));
	m_pTotalText->AddComponent(new TextComponent("HIGH SCORE", font18, TextAllignment::Middle));
	m_pTotalText->GetComponent<TextComponent>()->SetColor(dae::Colors::Red);
	SCENEMANAGER.GetActiveScene().Add(m_pTotalText);

	m_pPlayer2Text = new GameObject();
	m_pPlayer2Text->AddComponent(new TransformComponent());
	m_pPlayer2Text->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth - (windowWidth / 5), windowHeight - 20.f, 0));
	m_pPlayer2Text->AddComponent(new TextComponent("2UP", font18, TextAllignment::Middle));
	m_pPlayer2Text->GetComponent<TextComponent>()->SetColor(dae::Colors::SkyBlue);
	SCENEMANAGER.GetActiveScene().Add(m_pPlayer2Text);


	//DYNAMIC TEXT's (SCORES)
	m_pPlayer1ScoreText = new GameObject();
	m_pPlayer1ScoreText->AddComponent(new TransformComponent());
	m_pPlayer1ScoreText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 5, windowHeight - 40.0f, 0));
	m_pPlayer1ScoreText->AddComponent(new TextComponent("00", font18, TextAllignment::Middle));
	SCENEMANAGER.GetActiveScene().Add(m_pPlayer1ScoreText);

	m_pPlayer2ScoreText = new GameObject();
	m_pPlayer2ScoreText->AddComponent(new TransformComponent());
	m_pPlayer2ScoreText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth - (windowWidth / 5), windowHeight - 40.f, 0));
	m_pPlayer2ScoreText->AddComponent(new TextComponent("00", font18, TextAllignment::Middle));
	SCENEMANAGER.GetActiveScene().Add(m_pPlayer2ScoreText);

	m_pTotalScoreText = new GameObject();
	m_pTotalScoreText->AddComponent(new TransformComponent());
	m_pTotalScoreText->GetComponent<TransformComponent>()->SetPosition(FVector3(windowWidth / 2, windowHeight - 40.0f, 0));
	m_pTotalScoreText->AddComponent(new TextComponent("000000", font18, TextAllignment::Middle));
	SCENEMANAGER.GetActiveScene().Add(m_pTotalScoreText);


}

void dae::UIComponent::Update(float)
{

}

void dae::UIComponent::Render()
{
}

const std::string dae::UIComponent::GetComponentName() const
{
	return std::string();
}
