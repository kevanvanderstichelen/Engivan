#pragma once

namespace dae
{
	class TransformComponent;
	class BaseComponent;
	class Texture2D;
	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Initialize();
		void Update(float elapsed);
		void Render() const;

		void AddComponent(dae::BaseComponent* component);
		void RemoveComponent(dae::BaseComponent* component);

		TransformComponent* GetTransformComponent();

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

	private:
		TransformComponent* m_pTransform;
		std::shared_ptr<Texture2D> m_Texture{};
		std::vector<BaseComponent*> m_pComponents;
	};
}
