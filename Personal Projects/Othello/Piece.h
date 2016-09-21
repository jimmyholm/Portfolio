#pragma	once

#include "Sprite.h"
#include "AnimationManager.h"
#include "utility.h"

enum PieceState { NONE, BLACK, BLACK_FLIP, WHITE, WHITE_FLIP};

class Piece
{
	private:
		Sprite* sprite;
		char State;
	public:
		Piece(Pos2D pos, std::string Side);
		char GetState();
		void Update(Uint32 tick);
		void Draw();
		void Destroy();
		bool Flipping();
		void Flip();
		void SetState(char state);
};