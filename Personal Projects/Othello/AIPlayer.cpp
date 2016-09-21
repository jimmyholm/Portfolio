#include "AIPlayer.h"


AIPlayer::AIPlayer(MainGameScreen* screen, char playerType)
{
	Screen = screen;
	PlayerType = playerType;
	LastUpdate = (Uint32) -1;
	TimeCnt = 0;
	Delay = 1500;
	showMoves = false;
}


Pos2D AIPlayer::MakeTurn()
{
	Uint32 Tick = SDL_GetTicks();
	if(LastUpdate == (Uint32)-1)
		LastUpdate = Tick;
	if(LastUpdate != (Uint32)-1)
	{
		TimeCnt += Tick - LastUpdate;
		if(TimeCnt >= Delay)
		{
			Move** moves = Screen->GetMoves();
			int mx = 0, my;
			int tm = -1;
			for(int y = 0; y < 8; y++)
			{
				for(int x = 0; x < 8; x++)
				{
					if(moves[x+y*8]->GetCaptures() > tm)
					{
						mx = x;
						my = y;
						tm = moves[x+y*8]->GetCaptures();
					}
				}
			}
			TimeCnt = 0;
			LastUpdate = (Uint32)-1;
			return Pos2D((float)mx, (float)my);
		}
	}
	LastUpdate = Tick;
	return Pos2D(-1.0f, -1.0f);
}