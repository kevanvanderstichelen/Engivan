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
		virtual ~SceneManager();
		void AddScene(Scene* scene);
		void Initialize();
		void Update(float elapsed);
		void Render();
		void SetActiveScene(const std::string& name);
		Scene& GetActiveScene();
		Scene* GetPtrActiveScene();
		std::vector<Scene*> GetAllScenes() const { return m_pScenes; }
	private:
		friend class Singleton<SceneManager>;
		SceneManager() = default;
		std::vector<Scene*> m_pScenes;
		Scene* m_pCurrentScene;
	};
}
