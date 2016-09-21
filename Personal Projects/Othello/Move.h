#pragma once

#include "utility.h"
#include <list>
class Move
{
	protected:
		std::list<Pos2D> Cells;
		int Captures;
	public:
		Move();
		Move(Move* move);
		int GetCaptures();
		std::list<Pos2D> GetCells();
		void AddCell(Pos2D pos);
		~Move();
};