#include "Piece.h"

void Piece::Draw()
{
	if(State != NONE)
		sprite->Draw();
}

char Piece::GetState()
{
	return State;
}

void Piece::Update(Uint32 tick)
{
	sprite->Update(tick);
	if(!Flipping() && (State == BLACK_FLIP || State == WHITE_FLIP))
	{
		State = (State == BLACK_FLIP) ? WHITE : BLACK;
		(State == BLACK) ? sprite->SetAnimation("Black") : sprite->SetAnimation("White");
	}
}

Piece::Piece(Pos2D position, std::string side)
{
	Pos2D pos;
	pos.x = position.x*64 + 298;
	pos.y = position.y*64 + 32;
	sprite = new Sprite();
	if(side != "None")
	{
		sprite->MakeSprite("Piece", side);
		sprite->SetPosition(pos);
		State = (side == "Black") ? BLACK : WHITE;
	}
	else
	{
		sprite->MakeSprite("Piece","");
		sprite->SetPosition(pos);
		State = NONE;
	}
}

void Piece::Destroy()
{
	sprite->Destroy();
	delete sprite;
}

bool Piece::Flipping()
{
	if(sprite == NULL)
		return false;
	return (sprite->IsAnimating() && (	sprite->GetAnimationName() == "BlackFlip" || 
										sprite->GetAnimationName() == "WhiteFlip"));
}

void Piece::Flip()
{
	if(State == BLACK)
	{
		State = BLACK_FLIP;
		sprite->SetAnimation("BlackFlip");
	}
	else if(State = WHITE)
	{
		State = WHITE_FLIP;
		sprite->SetAnimation("WhiteFlip");
	}		
}

void Piece::SetState(char state)
{
	State = state;
	if(State == BLACK)
		sprite->SetAnimation("Black");
	else
		sprite->SetAnimation("White");
}