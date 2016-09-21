#pragma once

#include "Player.h"
#include "Move.h"
#include "MainGameScreen.h"

class AIPlayer : public Player
{
	private:
		MainGameScreen* Screen;
		Uint32 Delay;
		Uint32 TimeCnt;
		Uint32 LastUpdate;
	public:
		AIPlayer(MainGameScreen* screen, char playerType);
		Pos2D MakeTurn();
};