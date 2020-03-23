#pragma once
#include "Singleton.h"
#include <string>
#include <vector>
#include <memory>
namespace dae
{
	class Scene;
	class SceneManager final : public Singleton<SceneManager>
	{
	public:
		~SceneManager();
		void AddScene(Scene* scene);
		void Initialize();
		void Update(float elapsed);
		void Render();
		void SetActiveScene(const std::string& name);
		Scene& GetActiveScene();
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene;
	};
}
