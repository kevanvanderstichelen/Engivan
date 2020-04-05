#pragma once
#include "Singleton.h"
namespace dae
{
	class MainGame : public Singleton<MainGame>
	{
	public:
		void Initialize();
	private:
	};

}

