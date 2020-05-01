#pragma once
#include "Devlog.h"
#include "AudioManager.h"
namespace dae
{
	class Command
	{
	public:
		virtual ~Command() {}
		virtual void Execute(GameObject* gameObject = nullptr) = 0;
	};

	//TODO: Make class inherited from Command Class
	//Assign to InputManager with relevant buttons to execute them
	class TestCommand final : public Command
	{
	public:
		virtual void Execute(GameObject*) override
		{ 
			AudioManager::GetService().PlayMusic(1);
		};


	};



}
