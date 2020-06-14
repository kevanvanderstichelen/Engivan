#pragma once
#include "GameObject.h"
#include "MainStructs.h"
class Pickup
{
};

namespace dae
{
	class SpriteComponent;
	class Pickup final : public GameObject
	{
	public:
		explicit Pickup(const std::string& name, const int& points);
		virtual ~Pickup();
		Pickup(const Pickup& other) = delete;
		Pickup(Pickup&& other) = delete;
		Pickup& operator=(const Pickup& other) = delete;
		Pickup& operator=(Pickup&& other) = delete;

	protected:
		virtual void Initialize() override;
		virtual void Update(float elapsed) override;
		virtual void Render() const override;
	private:
		const int m_Points;
		const std::string m_Name;
		bool m_IsPickedUp = false;
		float m_Elapsed;
		const float m_ScoreExistanceTime = 1.0f;
		void CallBack(GameObject* current, GameObject* other);
	};

}