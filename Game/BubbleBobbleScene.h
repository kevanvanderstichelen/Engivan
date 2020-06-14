#pragma once
#include "Scene.h"
#include "Command.h"
#include "InputManager.h"
#include "RigidBodyComponent.h"
#include "StateMachine.h"
#include "LevelLoader.h"
namespace dae
{
	class LoggedAudio;

	class BubbleBobbleScene final : public Scene
	{
	public:
		BubbleBobbleScene();
		~BubbleBobbleScene();

		BubbleBobbleScene(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene(BubbleBobbleScene&& other) noexcept = delete;
		BubbleBobbleScene& operator=(const BubbleBobbleScene& other) = delete;
		BubbleBobbleScene& operator=(BubbleBobbleScene&& other) noexcept = delete;

		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;

		void SetNextLevel();
		const FPoint2& GetSpawnPoint(const uint& id);

		void AddPlayer(GameObject* player) { m_pPlayers.push_back(player); }
		std::vector<GameObject*>& GetPlayers() { return m_pPlayers; }

		void DeductEnemyCount() { m_EnemyCount--; }
		
	private:
		int m_EnemyCount;
		LoggedAudio* m_pAudioService = nullptr;
		GameObject* m_Avatar[2];
		GameObject* m_Box = nullptr;
		GameObject* m_Box2 = nullptr;
		LevelLoader m_Level1;
		LevelLoader m_Level2;
		LevelLoader m_Level3;
		bool m_LevelComleted = false;
		int m_CurrentLevel = 0;
		const float m_LevelTransitionSpeed = 250.f;

		FPoint2 m_PlayerSpawnPoint[2]{};
		std::vector<GameObject*> m_pPlayers;

		void SpawnLevel1Enemies();
		void SpawnLevel2Enemies();
		void SpawnLevel3Enemies();
	};

}


