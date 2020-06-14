#pragma once
#include "GameObject.h"
namespace dae
{
	template <class T>
	class ObjectPool final
	{
		static_assert(std::is_base_of<GameObject, T>::value, "ObjectPool Type must derive from Base class GameObject!");

	public:
		
		ObjectPool(size_t amount);
		~ObjectPool();
		ObjectPool(const ObjectPool&) = delete;
		ObjectPool(ObjectPool&&) = delete;
		ObjectPool& operator= (const ObjectPool&) = delete;
		ObjectPool& operator= (const ObjectPool&&) = delete;

		T* Acquire();
		void Release(T* Release);


	private:
		const size_t m_Size;
		T* m_pObjects = nullptr;
	};

	template<class T>
	inline ObjectPool<T>::ObjectPool(size_t amount)
		:m_Size(amount)
	{
		m_pObjects = new T[m_Size];
	}

	template<class T>
	inline ObjectPool<T>::~ObjectPool()
	{
		delete[] m_pObjects;
	}

	template<class T>
	inline T* ObjectPool<T>::Acquire()
	{
		auto obj = reinterpret_cast<GameObject*>(T);
		
		for (size_t i = 0; i < m_Size; i++)
		{
			auto obj = reinterpret_cast<GameObject*>(m_pObjects[i]);
			if (!obj->IsActive())
			{
				obj->SetActive(true);
				return obj;

			}
		}

		return NULL;
	}

	template<class T>
	inline void ObjectPool<T>::Release(T* Release)
	{
		for (size_t i = 0; i < m_Size; i++)
		{
			auto obj = reinterpret_cast<GameObject*>(m_pObjects[i]);
			if (obj == Release)
			{
				obj->SetActive(false);
			}
		}
	}

}
