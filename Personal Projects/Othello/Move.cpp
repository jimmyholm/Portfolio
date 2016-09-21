#include "Move.h"

int Move::GetCaptures()
{
	return Captures;
}

std::list<Pos2D> Move::GetCells()
{
	return Cells;
}

void Move::AddCell(Pos2D pos)
{
	Cells.push_back(pos);
	Captures++;
}

Move::Move()
{
	Captures = 0;
}

Move::~Move()
{
	Cells.clear();
}
Move::Move(Move* move)
{
	Captures = move->Captures;
	std::list<Pos2D> cmove = move->GetCells();
	Cells.resize(cmove.size());
	std::copy(cmove.begin(), cmove.end(), Cells.begin());
}