#include "MainGameScreen.h"


bool MainGameScreen::Update(Uint32 TickDelta)
{
	if(WaitForPlayAgain == false)
	{
		for(int i = 0; i < 64; i++)
		{
			Board[i]->Update(TickDelta);
		}
		if(CurrentPlayer == PS_BLACK && Players[0] != NULL)
		{
			Pos2D Cell = Players[0]->MakeTurn();
			if(Cell.x >= 0 && Cell.x < 8 && Cell.y >= 0 && Cell.y < 8)
			{
				if(AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCaptures() > 0)
				{
					Board[(int)(Cell.x + Cell.y*8)]->SetState(BLACK);
					CurrentPlayer = PS_WHITEFLIP;
					Flips = AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCells();
					curFlip = Flips.rbegin();
					LastFlip = FlipDelay;
					if(AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCaptures() > 4)
					{
						TxtMgr->DrawJumpingText("LargeFont", "NICE!", Pos2D(512, 200), 
							Tint(random(0.75f, 1.0f), random(0.5f, 1.0f), random(0.5f, 1.0f), 1.0f), 3500, Pos2D(0, -300.0f));
						int mp = random(2,5);
						Pos2D pos(0,0);
						for(int i = 0; i < mp; i++)
						{
							pos.x = random(298.0f, 746.0f);
							pos.y = random(32.0f, 480.0f);
							Particles->AddEmitter(ConfettiEmitter::CreateEmitter("Particle", pos, random(200,500), 
								Pos2D(0.1f, 0.1f), Pos2D(0.2f, 0.2f),
								Pos2D(-100.0f, -250.0f), Pos2D(100.0f, -150.0f), Pos2D(20.0f, 75.0f), Pos2D(0.0f, 10.0f),
								-10.0f, 10.0f, 10.0f, 2500));
						}
					}
				}
			}
		}
		else if(CurrentPlayer == PS_WHITE && Players[1] != NULL)
		{
			Pos2D Cell = Players[1]->MakeTurn();
			if(Cell.x >= 0 && Cell.x < 8 && Cell.y >= 0 && Cell.y < 8)
			{
				if(AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCaptures() > 0)
				{
					Board[(int)(Cell.x + Cell.y*8)]->SetState(WHITE);
					CurrentPlayer = PS_BLACKFLIP;
					Flips = AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCells();
					curFlip = Flips.rbegin();
					LastFlip = FlipDelay;
					if(AvailableMoves[(int)(Cell.x + Cell.y*8)]->GetCaptures() > 4)
					{
						TxtMgr->DrawJumpingText("LargeFont", "NICE!", Pos2D(512, 200), 
							Tint(random(0.75f, 1.0f), random(0.5f, 1.0f), random(0.5f, 1.0f), 1.0f), 3500, Pos2D(0, -300.0f));
						int mp = random(2,5);
						Pos2D pos(0,0);
						for(int i = 0; i < mp; i++)
						{
							pos.x = random(298.0f, 746.0f);
							pos.y = random(32.0f, 480.0f);
							Particles->AddEmitter(ConfettiEmitter::CreateEmitter("Particle", pos, random(200,500), 
								Pos2D(0.1f, 0.1f), Pos2D(0.2f, 0.2f),
								Pos2D(-100.0f, -250.0f), Pos2D(100.0f, -150.0f), Pos2D(20.0f, 75.0f), Pos2D(0.0f, 10.0f),
								-10.0f, 10.0f, 10.0f, 2500));
						}
					}
				}
			}
		}
		else if(CurrentPlayer == PS_WHITEFLIP || PS_BLACKFLIP)
		{
			if(Flips.size() != 0)
			{
				if(curFlip == Flips.rend())
				{
					if(!IsFlipping())
					{
						Flips.clear();
						ChangeTurn();
					}
				}
				else
				{
					LastFlip += TickDelta;
					while(LastFlip >= FlipDelay && curFlip != Flips.rend())
					{
						int x = (int)(*curFlip).x;
						int y = (int)(*curFlip).y;
						Board[x+y*8]->Flip();
						LastFlip -= FlipDelay;
						curFlip++;
						if(CurrentPlayer == PS_WHITEFLIP)
						{
							WhiteCount--;
							BlackCount++;
						}
						else
						{
							BlackCount--;
							WhiteCount++;
						}
					}
				}
			}
		}
		if(GameOver)
		{
			int BCount = 0, WCount = 0;
			char win = CheckWinner(BCount, WCount);
			if(win == BLACK)
			{
				Winner = BLACK;
				TxtMgr->DrawJumpingText("LargeFont", FormatString("Black wins with %d pieces against %d pieces!", BCount, WCount), Pos2D(512, 300), Tint(0.0f, 0.0f, 0.0f, 1.0f), 2000, Pos2D(0.0f, -500.0f));
			}
			else if(win == WHITE)
			{
				Winner = WHITE;
				TxtMgr->DrawJumpingText("LargeFont", FormatString("White wins with %d pieces against %d pieces!", WCount, BCount), Pos2D(512, 300), Tint(0.0f, 0.0f, 0.0f, 1.0f), 2000, Pos2D(0.0f, -500.0f));
			}
			else
			{
				Winner = NONE;
				TxtMgr->DrawJumpingText("LargeFont", FormatString("Game tied at %d pieces!", WCount), Pos2D(512, 300), Tint(0.0f, 0.0f, 0.0f, 1.0f), 2000, Pos2D(0.0f, -500.0f));
			}
			GameOver = false;
			WaitForPlayAgain = true;
		}
	}
	else
	{
		int btn = Buttons->Update();
		if(btn == IDYES)
		{
			Player* p2 = Players[1];
			SetPlayer(1, Players[0]);
			SetPlayer(0, p2);
			Reset();
		}
		else if(btn == IDNO)
		{
			return false; // Pop this screen and go back to the main menu!
		}
	}
	return true;
}

void MainGameScreen::Draw()
{
	Background->Draw(0, 0, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, false, 0.0f);
	if(ShowMoves && (CurrentPlayer != PS_BLACKFLIP && CurrentPlayer != PS_WHITEFLIP))
	{
		if(Players[CurrentPlayer]->ShowMoves())
		{
			for(int x = 0; x < 8; x++)
			{
				for(int y = 0; y < 8; y++)
				{
					if(AvailableMoves[x+(y*8)]->GetCaptures() > 0)
					{
						ValidMove->Draw(266+(x*64.0f), y*64.0f, 1.0f, 1.0f, 1.0f, 0.5f, 1.0f, 1.0f, false, 0);
					}
				}
			}
		}
	}
	for(int i = 0; i < 64; i++)
	{
		Board[i]->Draw();
	}
	int x = 0;
	int y = 0;
	Pos2D pos;
	Texture* p = TextureMgr->getTexture("BlackPiece");
	for(int i = 0; i < BlackCount; i++)
	{
		pos.x = (float)(32 + (x*32) + 16);
		pos.y = (float)(46 + (y*32) + 16 + (y*2));
		p->Draw(pos.x, pos.y, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, true, 0.0f);
		x++;
		if(x >= 6)
		{
			x = 0;
			y++;
		}
	}
	x = 0; y = 0;
	p->Release();
	p = TextureMgr->getTexture("WhitePiece");
	for(int i = 0; i < WhiteCount; i++)
	{
		pos.x = (float)(808 + (x*32) + 16);
		pos.y = (float)(46 + (y*32) + 16 + (y*2));
		p->Draw(pos.x, pos.y, 1.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f, true, 0.0f);
		x++;
		if(x >= 6)
		{
			x = 0;
			y++;
		}
	}
	p->Release();
	if(WaitForPlayAgain)
	{
		if(Winner == BLACK)
			TxtMgr->DrawStaticText("LargeFont", "Black Won!", Pos2D(512,256), TINT_RED);
		else if(Winner == WHITE)
			TxtMgr->DrawStaticText("LargeFont", "White Won!", Pos2D(512,256), TINT_RED);
		else if(Winner == NONE)
			TxtMgr->DrawStaticText("LargeFont", "Draw Game!", Pos2D(512,256), TINT_RED);
		TxtMgr->DrawStaticText("LargeFont", "Swap players and play again?", Pos2D(512, 300), TINT_RED);
		Buttons->Draw();
	}
	TxtMgr->DrawStaticText("SmallFont", FormatString("Black Wins: %d", BlackWins), Pos2D(95, 435), TINT_BLK);
	TxtMgr->DrawStaticText("SmallFont", FormatString("White Wins: %d", WhiteWins), Pos2D(870, 435), TINT_WHT);
}

void MainGameScreen::Destroy()
{
	for(int i = 0; i < 64; i++)
	{
		Board[i]->Destroy();
		delete Board[i];
	}
	for(int i = 0; i < 64; i++)
	{
		delete AvailableMoves[i];
		AvailableMoves[i] = NULL;
	}
	delete[] AvailableMoves;
	Buttons->DestroyButton(IDYES);
	Buttons->DestroyButton(IDNO);
	Buttons->DestroyManager();
	delete Buttons;
	Background->Release();
	ValidMove->Release();
	TextureMgr->UnloadScript("Piece");
	TextureMgr->UnloadTexture("MainBackground");
	TextureMgr->UnloadTexture("ValidMove");
	TxtMgr->UnloadFont("LargeFont");
	TxtMgr->UnloadFont("SmallFont");
}

void MainGameScreen::Initialize()
{
	TxtMgr = TextManager::GetInstance();
	Particles = ParticleEngine::GetInstance();
	TxtMgr->LoadFont("LargeFont", "FreeSerifBold.ttf", 60);
	TxtMgr->LoadFont("SmallFont", "FreeSerifBold.ttf", 20);
	TextureMgr->LoadTexture("MainBackground", "gfx/GameScreen.tga");
	TextureMgr->LoadTexture("ValidMove", "gfx/OkSquare.tga");
	ValidMove = TextureMgr->getTexture("ValidMove");
	Background = TextureMgr->getTexture("MainBackground");
	TextureMgr->LoadScript("Piece", "PieceTextureScript.txt");
	AnimationManager::GetInstance()->LoadScript("Piece", "PieceSpriteScript.txt");
	ShowMoves = true;
	BlackWins = 0;
	WhiteWins = 0;
	Buttons = new ButtonManager();
	Buttons->AddButton(Button::CreateButton(Pos2D(480,400), Pos2D(50,32), "FreeSerif25", "Yes", IDYES, 
						"ButtonUp", "ButtonOver", "ButtonDown", TINT_BLK));//new Button(Pos2D(480,500), "FreeSerif25", "Yes", IDYES));
	Buttons->AddButton(Button::CreateButton(Pos2D(544,400), Pos2D(50,32), "FreeSerif25", "No", IDNO, 
						"ButtonUp", "ButtonOver", "ButtonDown", TINT_BLK));//new Button(Pos2D(544,500), "FreeSerif25", "No", IDNO));

	AvailableMoves = NULL;
	Reset();
	//WaitForPlayAgain = true;
}
void MainGameScreen::Reset()
{
	for(int x = 0; x < 8; x++)
	{
		for(int y = 0; y < 8; y++)
		{
			if(x == 3 && y == 3)
				Board[x+(y*8)] = new Piece(Pos2D((float)x,(float)y), "White");
			else if(x == 4 && y == 3)
				Board[x+(y*8)] = new Piece(Pos2D((float)x,(float)y), "Black");
			else if(x == 3 && y == 4)
				Board[x+(y*8)] = new Piece(Pos2D((float)x,(float)y), "Black");
			else if(x == 4 && y == 4)
				Board[x+(y*8)] = new Piece(Pos2D((float)x,(float)y), "White");
			else
			{
				Board[x+(y*8)] = new Piece(Pos2D((float)x,(float)y), "White");
				Board[x+(y*8)]->SetState(NONE);
			}
		}
	}
	
	WaitForPlayAgain = false;
	GameOver = false;
	if(AvailableMoves != NULL)
		delete AvailableMoves;
	AvailableMoves = new Move*[64];
	for(int i = 0; i < 64; i++)
	{
		AvailableMoves[i] = NULL;
	}
	memset(AvailableMoves, 0, sizeof(Move*)*64);
	CurrentPlayer = PS_BLACK;
	FlipDelay = 218;
	LastFlip = 0;
	LastPass = false;
	CheckMoves();
}
bool MainGameScreen::IsFlipping()
{
	for(int i = 0; i < 64; i++)
	{
		if(Board[i]->Flipping())
			return true;
	}
	return false;
}
void MainGameScreen::ChangeTurn()
{
	for(int i = 0; i < 64; i++)
	{
		delete AvailableMoves[i];
		AvailableMoves[i] = NULL;
	}
	if(CurrentPlayer == PS_WHITEFLIP)
	{
		TxtMgr->DrawTimedText("LargeFont", "White's Turn", Pos2D(512, 256), Tint(0.0f, 0.0f, 0.0f, 1.0f), 1000);
		CurrentPlayer = PS_WHITE;
	}
	else
	{
		TxtMgr->DrawTimedText("LargeFont", "Black's Turn", Pos2D(512, 256), Tint(0.0f, 0.0f, 0.0f, 1.0f), 1000);
		CurrentPlayer = PS_BLACK;
	}
	CheckMoves();
	if(NumAvailableMoves == 0)
	{
		if(LastPass == false)
		{
			LastPass = true;
			if(CurrentPlayer == PS_BLACK)
				TxtMgr->DrawJumpingText("LargeFont", "No available moves for Black!", Pos2D(512, 156), Tint(0.0f, 0.0f, 0.0f, 1.0f), 2000, Pos2D(0.0f, -500.0f));
			else
				TxtMgr->DrawJumpingText("LargeFont", "No available moves for White!", Pos2D(512, 156), Tint(0.0f, 0.0f, 0.0f, 1.0f), 2000, Pos2D(0.0f, -500.0f));
			ChangeTurn();
		}
		else
		{
			GameOver = true;
		}
	}
	else
		LastPass = false;
}

char MainGameScreen::CheckWinner(int& BCount, int& WCount)
{
	for(int i = 0; i < 64; i++)
	{
		if(Board[i]->GetState() == BLACK)
			BCount++;
		else if(Board[i]->GetState() == WHITE)
			WCount++;
	}
	if(BCount > WCount)
	{
		BlackWins++;
		return BLACK;
	}
	if(WCount > BCount)
	{
		WhiteWins++;
		return WHITE;
	}
	return NONE;
}

void MainGameScreen::CheckMoves()
{
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			if(AvailableMoves[x+y*8] != NULL)
			{
				delete AvailableMoves[x+y*8];
				AvailableMoves[x+y*8] = NULL;
			}
		}
	}
	NumAvailableMoves = 0;
	for(int y = 0; y < 8; y++)
	{
		for(int x = 0; x < 8; x++)
		{
			Move* move = new Move();
			if(Board[x+(y*8)]->GetState() == NONE) // Empty space, lessee if it's a valid move!
			{				
				// Look right
				Pos2D pos((float)x,(float)y);
				while(true)
				{
					pos.x++;
					if(pos.x >= 8) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(--pos.x > x)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look down-right
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.x++; pos.y++;
					if(pos.x >= 8 || pos.y >= 8) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(--pos.x > x && --pos.y > y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look down
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.y++;
					if(pos.y >= 8) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(--pos.y > y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look down-left
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.x--; pos.y++;
					if(pos.x < 0 || pos.y >= 8) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(++pos.x < x && --pos.y > y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look left
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.x--;
					if(pos.x < 0) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(++pos.x < x)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look up-left
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.x--; pos.y--;
					if(pos.x < 0 || pos.y < 0) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(++pos.x < x && ++pos.y < y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look up
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.y--;
					if(pos.y < 0) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(++pos.y < y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
				// Look up-right
				pos = Pos2D((float)x,(float)y);
				while(true)
				{
					pos.x++; pos.y--;
					if(pos.x >= 8 || pos.y < 0) // Make sure we don't hop outside the board
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == NONE)
						break;
					if(Board[(int)(pos.x+(pos.y*8))]->GetState() == ((CurrentPlayer == PS_BLACK) ? BLACK : WHITE))
					{
						while(--pos.x > x && ++pos.y < y)
						{
							move->AddCell(pos);
						}
						break;
					}
				}
			}
			AvailableMoves[x+y*8] = new Move(move);	
			if(move->GetCaptures() > 0)
				NumAvailableMoves++;
			delete move;
		}
	}
	CountPieces();
}
void MainGameScreen::CountPieces()
{
	BlackCount = 0; WhiteCount = 0;
	for(int i = 0; i < 64; i++)
	{
		if(Board[i]->GetState() == BLACK)
			BlackCount++;
		else if(Board[i]->GetState() == WHITE)
			WhiteCount++;
	}
}
void MainGameScreen::SetPlayer(int index, Player* player)
{
	if(index > -1 && index < 8)
		Players[index] = player;
}

Move** MainGameScreen::GetMoves()
{
	return AvailableMoves;
}