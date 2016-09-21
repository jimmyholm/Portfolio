#pragma once
#include "Utility.h"

enum e_PlayerType { PLAYER_BLACK, PLAYER_WHITE, PLAYER_OBSERVER};

class Player
{
	protected:
		int PlayerType;
		std::string name;
		bool showMoves;
	public:
		virtual Pos2D MakeTurn() = 0; // Return the cell to place a piece - the main game screen determines if it's valid.
		std::string GetName()
		{
			return name;
		}
		int GetPlayerType()
		{
			return PlayerType;
		}
		bool ShowMoves() { return showMoves;}
};