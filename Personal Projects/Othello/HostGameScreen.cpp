#include "HostGameScreen.h"

void HostGameScreen::Setup()
{
	ScreenMgr = GameScreenManager::GetInstance();
	Input = InputHandler::GetInstance();
	TxtMgr = TextManager::GetInstance();
	TxtMgr->LoadScript("Fonts", "Fonts.txt");
	LocalGame = CheckBox::CreateCheckbox(Pos2D(100, 100), "", "", true, false);
	RemoteGame = CheckBox::CreateCheckbox(Pos2D(100, 100), "", "", false, false);
}

void HostGameScreen::Destroy()
{
	LocalGame->Destroy();
	RemoteGame->Destroy();
	TxtMgr->UnloadScript("Fonts");
}