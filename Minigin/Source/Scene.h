#pragma once
#include "SceneManager.h"
#include <vector>
#include <string>
#include "SceneManager.h"
#include "CameraComponent.h"

namespace dae
{
	class GameObject;
	class Scene
	{
	public:
		explicit Scene(const std::string& name);
		virtual ~Scene();
		Scene(const Scene& other) = delete;
		Scene(Scene&& other) = delete;
		Scene& operator=(const Scene& other) = delete;
		Scene& operator=(Scene&& other) = delete;

		virtual void Initialize() = 0;
		virtual void Update(float elapsed) = 0;
		virtual void Render() const = 0;

		const std::string& GetName() { return m_Name; }
		void Add(GameObject* object);
		void Remove(GameObject* object);

		void SetActiveCamera(CameraComponent* pCamera);
		CameraComponent* GetActiveCamera() { return m_pCameraComponent; }

	protected:


	private: 
		const std::string m_Name;
		std::vector<GameObject*> m_pGameObjects;

		static unsigned int m_IdCounter; 

		friend class SceneManager;
		void RootInitialize();
		void RootUpdate(float elapsed);
		void RootRender() const;

		CameraComponent* m_pCameraComponent;
	};

}
