#pragma once

#include "utility.h"
#include "GameScreen.h"
#include "Player.h"
#include "Piece.h"
#include "Move.h"
#include "TextManager.h"
#include "ParticleEngine.h"
#include "ButtonManager.h"
enum PlayerStates { PS_BLACK, PS_WHITE, PS_BLACKFLIP, PS_WHITEFLIP};

class MainGameScreen : public GameScreen
{
	private:
		ParticleEngine*		Particles;
		TextManager*		TxtMgr;
		Piece*				Board[64];
		Move**				AvailableMoves;
		Player*				Players[8];
		char				CurrentPlayer;
		Texture*			Background;
		Texture*			ValidMove;
		bool				ShowMoves;
		std::list<Pos2D>	Flips;
		std::list<Pos2D>::reverse_iterator curFlip;
		Uint32				FlipDelay; // Delay between started piece-flips
		Uint32				LastFlip;
		int					WhiteCount;
		int					BlackCount;
		int					NumAvailableMoves;
		char				Winner;
		bool				LastPass; // Was the last move a pass?
		bool				GameOver; // Is the game over?
		void CheckMoves();		// Check for available moves
		void ChangeTurn();		// Change the turn to the next player.
		bool IsFlipping();		// Check if pieces are still flipping. The game is paused during flips and the turn
								// isn't handed over until all pieces are flipped.
		void CountPieces();
		char CheckWinner(int& BCount, int& WCount);		// Count pieces, return who won.

		void SwapPlayers();		// Swap the players
		bool WaitForPlayAgain;	// The game is over, the "play again" button is up; are we waiting?
		void Reset();
		int BlackWins;
		int WhiteWins;
		ButtonManager* Buttons;
	public:
		void Initialize();
		Move** GetMoves();
		virtual bool Update(Uint32 TickDelta); // Return false if this screen should be popped
		virtual void Draw();
		virtual void Destroy(); // De-initialize the screem; called when the screen is popped
		void SetPlayer(int index, Player* player);
		void EndGame();
		void NewGame();
};