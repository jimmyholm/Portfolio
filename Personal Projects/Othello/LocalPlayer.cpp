#include "LocalPlayer.h"

LocalPlayer::LocalPlayer(int playerType, Pos2D boardPosition)
{
	PlayerType = playerType;
	BoardPosition = boardPosition;
	showMoves = true;
}

Pos2D LocalPlayer::MakeTurn()
{
	if(InputHandler::GetInstance()->MouseDown(SDL_BUTTON_LEFT))
	{
		Pos2D pos = InputHandler::GetInstance()->GetMousePosition();
		pos.x -= 266;
		if(pos.x > 0 && pos.x < 512 && pos.y < 512) // The mouse is inside the board area
		{
			pos.x = (float)((int)pos.x/64); 
			pos.y = (float)((int)pos.y/64);
			return pos; // Return the rounded down row and column number
		}
	}
	return Pos2D(-1,-1);
}