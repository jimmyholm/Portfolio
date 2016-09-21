#include "MainMenuScreen.h"
#include "MainGameScreen.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
MainMenuScreen::MainMenuScreen()
{
	TextureMgr->LoadScript("Main Menu", "MainMenuTexture.txt");

	HostGame[0] = TextureMgr->getTexture("Host Game");
	HostGame[1] = TextureMgr->getTexture("Host Game Selected");
	JoinGame[0] = TextureMgr->getTexture("Join Game");
	JoinGame[1] = TextureMgr->getTexture("Join Game Selected");
	Exit[0] = TextureMgr->getTexture("Exit");
	Exit[1] = TextureMgr->getTexture("Exit Selected");
	Background = TextureMgr->getTexture("Main Menu Screen");
	HostPos = Pos2D(512, 314);
	JoinPos = Pos2D(512, 442);
	ExitPos = Pos2D(512, 570);
	Selection = SELECTION_HOST;
	Input = InputHandler::GetInstance();
	ScreenMgr = GameScreenManager::GetInstance();
	RepeatDelay = 0;
	mGame = NULL;
}

bool MainMenuScreen::Update(Uint32 TickDelta)
{
	if(Input->KeyDown(SDLK_UP) || (Input->KeyHeld(SDLK_UP) && RepeatDelay >= 200))
	{
		RepeatDelay = 0;
		Selection--;
		if(Selection < SELECTION_HOST)
			Selection = SELECTION_EXIT;
	}
	if(Input->KeyDown(SDLK_DOWN) || (Input->KeyHeld(SDLK_DOWN) && RepeatDelay >= 200))
	{
		RepeatDelay = 0;
		Selection++;
		if(Selection > SELECTION_EXIT)
			Selection = SELECTION_HOST;
	}

	if(Input->KeyDown(SDLK_RETURN))
	{
		switch(Selection)
		{
			case SELECTION_HOST:
				// TODO: Add Host Game screen to the game-screen queue.
				mGame = new MainGameScreen();
				mGame->SetPlayer(0, new LocalPlayer(0,Pos2D(0,0)));
				mGame->SetPlayer(1, new AIPlayer(mGame, 1));
				ScreenMgr->PushScreen(mGame);
				break;
			case SELECTION_JOIN:
				// TODO: Add Join Game screen to the game-screen queue.
				break;
			case SELECTION_EXIT:
				return false;
				break;
		}
	}
	RepeatDelay += TickDelta;
	return true; // Don't pop this from the stack.
}

void MainMenuScreen::Draw()
{
	Background->Draw(0, 0, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, 0.0f);
	if(Selection == SELECTION_HOST)
		HostGame[1]->Draw(HostPos.x, HostPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	else
		HostGame[0]->Draw(HostPos.x, HostPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	if(Selection == SELECTION_JOIN)
		JoinGame[1]->Draw(JoinPos.x, JoinPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	else
		JoinGame[0]->Draw(JoinPos.x, JoinPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	if(Selection == SELECTION_EXIT)
		Exit[1]->Draw(ExitPos.x, ExitPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	else
		Exit[0]->Draw(ExitPos.x, ExitPos.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
}

void MainMenuScreen::Destroy()
{
	TextureMgr->UnloadScript("Main Menu");
	Selection = 0;
}