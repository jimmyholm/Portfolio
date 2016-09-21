#pragma once
#include "GameScreen.h"
#include <list>

class GameScreenManager
{
	private:
		static GameScreenManager* Instance;
		GameScreenManager();
		size_t NumScreens;
		std::list<GameScreen*> Screens;
		GameScreen* NextScreen; // If this isn't zero - the manager pushes this screen onto the stack first thing before the next update
	public:
		static GameScreenManager* GetInstance();

		void PushScreen(GameScreen* Screen);
		void PopScreen();
		void OneFrame(Uint32 TickDelta);
		void Render();
		void ShutDown(); // Destroy all screens
		size_t CountScreens();

		void SetNextScreen(GameScreen* Screen);
};