#include "GameScreenManager.h"

GameScreenManager* GameScreenManager::Instance = 0;

GameScreenManager* GameScreenManager::GetInstance()
{
	if(Instance == 0)
		Instance = new GameScreenManager;
	return Instance;
}

GameScreenManager::GameScreenManager() : NumScreens(0),  NextScreen(0)
{
}

void GameScreenManager::PushScreen(GameScreen *Screen)
{
	Screens.push_front(Screen);
	NumScreens++;
}

void GameScreenManager::PopScreen()
{
	if(NumScreens != 0)
	{
		(*Screens.begin())->Destroy();
		Screens.pop_front();
		NumScreens--;
	}
}

void GameScreenManager::OneFrame(Uint32 TickDelta)
{
	if(NumScreens != 0)
	{
		bool b = (*Screens.begin())->Update(TickDelta);
		if(b == false)
			PopScreen();
	}
	if(NextScreen != 0)
	{
		PushScreen(NextScreen);
		NextScreen = 0;
	}
}

void GameScreenManager::Render()
{
	if(NumScreens != 0)
	{
		(*Screens.begin())->Draw();
	}
}

void GameScreenManager::ShutDown()
{
	std::list<GameScreen*>::iterator it;
	for(it = Screens.begin(); it != Screens.end(); it++)
	{
		(*it)->Destroy();
		NumScreens--;
	}
	Screens.clear();
	delete Instance;
	Instance = NULL;
}

size_t GameScreenManager::CountScreens()
{
	return NumScreens;
}

void GameScreenManager::SetNextScreen(GameScreen* Screen)
{
	NextScreen = Screen;
}