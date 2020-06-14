#pragma once
#include <string>
#include <memory>
#include <vector>
namespace dae
{
	class TransformComponent;
	class BaseComponent;
	class Texture2D;
	class Scene;
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void RootInitialize();
		void RootUpdate(float elapsed);
		void RootRender() const;

		void AddComponent(dae::BaseComponent* component);
		void RemoveComponent(dae::BaseComponent* component);

		TransformComponent* GetTransform();

		template <class T>
		T* GetComponent()
		{
			const type_info& ti = typeid(T);
			for (auto* pComponent : m_pComponents)
			{
				if (pComponent && typeid(*pComponent) == ti)
					return static_cast<T*>(pComponent);
			}
			return nullptr;
		}

		void SetTag(const std::string& tag) { m_Tag = tag ; }
		const std::string& GetTag() const noexcept { return m_Tag; }

		void SetActive(const bool& enable) { m_IsActive = enable; }
		const bool& IsActive() const { return m_IsActive; }

		void AddChild(GameObject* object);
		void RemoveChild(GameObject* object);

		GameObject* GetParent() { return m_pParent; }
		void SetLinkedScene(Scene* pScene) { m_pLinkedScene = pScene; }
		Scene* GetLinkedScene() const { return m_pLinkedScene; }

	protected:
		virtual void Initialize() {};
		virtual void Update(float) {};
		virtual void Render() const {};
	private:
		bool m_IsInitialized = false;
		bool m_IsActive = true;
		TransformComponent* m_pTransform;
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<BaseComponent*> m_pComponents;
		std::vector<GameObject*> m_pChilderens;
		std::string m_Tag;
		GameObject* m_pParent = nullptr;
		Scene* m_pLinkedScene;
	};
}
