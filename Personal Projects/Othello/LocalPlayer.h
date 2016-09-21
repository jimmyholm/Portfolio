#pragma once

#include "Player.h"
#include "InputHandler.h"

class LocalPlayer : public Player
{
	protected:
		Pos2D BoardPosition;
		InputHandler* Input;

	public:
		LocalPlayer(int playerType, Pos2D boardPosition);
		virtual Pos2D MakeTurn();
};