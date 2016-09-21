#include "CMainGameScreen.h"
#include <boost\format.hpp>
#include <fstream>
CMainGameScreen::CMainGameScreen(char Level) : m_Level(Level), m_Score(0), m_HighScore(0)
{
	m_TexMgr = CSTextureManager::GetInstance();
}


void CMainGameScreen::MarkLine(unsigned int y)
{
	for(int x = 0; x < 10; x++)
		FillSquare(sf::Vector2i(x, y), CShape::EShapes::SHAPE_CLEAR);
}

void CMainGameScreen::CheckLines()
{
	int LinesToClear = 0;
	for(int y = 0; y < 20; y++)
	{
		if(FullLine(y))
		{
			LinesToClear++;
			MarkLine(y);
		}
	}
	if(LinesToClear != 0)
	{
		m_WaitForClear = true;
		while(LinesToClear > 0)
		{
			m_ScoreToAdd += LinesToClear*100;
			LinesToClear--;
		}
	}
}

void CMainGameScreen::DropLine(unsigned int y)
{
	if(y == 19)
		return;
	for(int x = 0; x < 10; x++)
	{
		m_Board[x+(y+1)*10] = m_Board[x+y*10];
		m_Board[x+y*10] = CShape::EShapes::SHAPE_EMPTY;
		FillSquare(sf::Vector2i(x,y), m_Board[x+y*10]);
		FillSquare(sf::Vector2i(x,y+1), m_Board[x+(y+1)*10]);
	}
}

bool CMainGameScreen::EmptyLine(unsigned int y)
{
	for(int x = 0; x < 10; x++)
	{
		if(m_Board[x+y*10] != CShape::EShapes::SHAPE_EMPTY)
			return false;
	}
	return true;
}

bool CMainGameScreen::FullLine(unsigned int y)
{
	for(int x = 0; x < 10; x++)
	{
		if(m_Board[x+y*10] == CShape::EShapes::SHAPE_EMPTY)
			return false;
	}
	return true;
}
// Return true when all lines are finished dropping.
bool CMainGameScreen::DropLines()
{
	bool Moved = false;
	for(int y = 19; y > 0; y--)
	{
		if(EmptyLine(y) && !EmptyLine(y-1))
		{
			DropLine(y-1);
			Moved = true;
		}
	}
	return Moved;
}

void CMainGameScreen::ClearLines()
{
	for(int y = 0; y < 20; y++)
	{
		if(m_Board[y*10] == CShape::EShapes::SHAPE_CLEAR)
		{
			for(int x = 0; x < 10; x++)
				FillSquare(sf::Vector2i(x,y), CShape::EShapes::SHAPE_EMPTY);
		}
	}
}
void CMainGameScreen::ProcessMessages()
{
	IMessage* msg = 0;
	while((msg = GetTop()) != NULL)
	{
		if(msg->m_MessageType == MSG_KEYBOARD)
		{
			MKeyboardMessage* kmsg= (MKeyboardMessage*)msg;
			if(kmsg->m_KeyState == MKeyboardMessage::KM_PRESSED)
			{
				if(kmsg->m_KeyEvent.code == sf::Keyboard::Escape)
					;
				else if(kmsg->m_KeyEvent.code == sf::Keyboard::Left && !m_WaitingForNext)
				{
					sf::Vector2i pos[4];
					m_Piece.GetPositions(pos);
					bool Ok = true;
					for(int i = 0; i < 4; i++)
					{
						if(pos[i].x-1 < 0)
						{
							Ok = false;
							break;
						}
					}
					if(Ok)
					{
						m_Piece.MoveLeft();
						sf::Vector2i test[4];
						m_Piece.GetPositions(test);
						Ok = true;
						for(int i = 0; i < 4; i++)
						{
							if(CheckCollision(test[i]) || test[i].x < 0 || test[i].x > 9)
							{
								Ok = false;
								break;
							}
						}
						if(!Ok)
							m_Piece.MoveRight();
					}
				}
				else if(kmsg->m_KeyEvent.code == sf::Keyboard::Right && !m_WaitingForNext)
				{
					sf::Vector2i pos[4];
					m_Piece.GetPositions(pos);
					bool Ok = true;
					for(int i = 0; i < 4; i++)
					{
						if(pos[i].x+1 > 9)
						{
							Ok = false;
							break;
						}
					}
					if(Ok)
					{
						m_Piece.MoveRight();
						sf::Vector2i test[4];
						m_Piece.GetPositions(test);
						Ok = true;
						for(int i = 0; i < 4; i++)
						{
							if(CheckCollision(test[i]) || test[i].x < 0 || test[i].x > 9)
							{
								Ok = false;
								break;
							}
						}
						if(!Ok)
							m_Piece.MoveLeft();
					}
				}
				else if(kmsg->m_KeyEvent.code == sf::Keyboard::Down && !m_WaitingForNext)
				{
					sf::Vector2i pos[4];
					m_Piece.GetPositions(pos);
					bool Ok = true;
					for(int i = 0; i < 4; i++)
					{
						if(pos[i].y+1 > 19)
						{
							Ok = false;
							break;
						}
					}
					if(Ok)
					{
						m_Piece.MoveDown();
						sf::Vector2i test[4];
						m_Piece.GetPositions(test);
						Ok = true;
						for(int i = 0; i < 4; i++)
						{
							if(CheckCollision(test[i]) || test[i].x < 0 || test[i].x > 9)
							{
								Ok = false;
								break;
							}
						}
						if(!Ok)
							m_Piece.MoveUp();
						else
						{
							if(CheckLanded())
								Land();
							m_TimeTilMove = MOVETIMEMAX;
						}
					}
				}
				else if(kmsg->m_KeyEvent.code == sf::Keyboard::A  && !m_WaitingForNext)
				{
					m_Piece.RotateRight();
					sf::Vector2i test[4];
					m_Piece.GetPositions(test);
					bool Ok = true;
					for(int i = 0; i < 4; i++)
					{
						if(CheckCollision(test[i]) || test[i].x < 0 || test[i].x > 9)
						{
							Ok = false;
							break;
						}
					}
					if(!Ok)
						m_Piece.RotateLeft();
				}
				else if(kmsg->m_KeyEvent.code == sf::Keyboard::D  && !m_WaitingForNext)
				{
					m_Piece.RotateLeft();
					sf::Vector2i test[4];
					m_Piece.GetPositions(test);
					bool Ok = true;
					for(int i = 0; i < 4; i++)
					{
						if(CheckCollision(test[i]) || test[i].x < 0 || test[i].x > 9)
						{
							Ok = false;
							break;
						}
					}
					if(!Ok)
						m_Piece.RotateRight();
				}
			}
		}
		delete msg;
	}
}

bool CMainGameScreen::Initialize()
{
	CPiece::SeedRandomizer();
	if(!m_TexMgr->IsTextureLoaded("GameBoard"))
		m_TexMgr->LoadTexture("GameBoard", "Resources\\Textures\\gameboard.tga");
	if(!m_TexMgr->IsTextureLoaded("Block"))
		m_TexMgr->LoadTexture("Block", "Resources\\Textures\\block.tga");
	m_GameBoard		= m_TexMgr->GetTexture("GameBoard");
	m_BlockTexture	= m_TexMgr->GetTexture("Block");
	std::ifstream f;
	f.open("Resources\\highscore", std::ios::in | std::ios::binary);
	if(f.is_open())
	{
		f.read((char*)&m_HighScore, sizeof(unsigned int));
		f.close();
	}
	else
		m_HighScore = 0;
	m_Font = CSBitmapFontManager::GetInstance()->GetFont("Font");
	m_Score = 0;
	m_ScoreToAdd = 0;
	std::string str;
	if(m_HighScore == 0)
		m_HighscoreText = m_Font->CreateText("--------", sf::Color::White);
	else
	{
		str = boost::str(boost::format("%|08|") % m_HighScore);
		m_HighscoreText = m_Font->CreateText(str, sf::Color::White);
	}
	m_ScoreText = m_Font->CreateText("00000000", sf::Color::White);
	str = boost::str(boost::format("%|02|") % (int)m_Level);
	m_LevelText = m_Font->CreateText(str, sf::Color::White);
	m_HighscoreTextPos = sf::Vector2f(494.0f, 104.0f);
	m_ScoreTextPos = sf::Vector2f(494.0f, 200.0f);
	m_LevelTextPos = sf::Vector2f(548.0f, 296.0f);
	m_HighscoreText->setPosition(m_HighscoreTextPos);
	m_HighscoreText->setOrigin(0,0);
	m_ScoreText->setPosition(m_ScoreTextPos);
	m_ScoreText->setOrigin(0,0);
	m_LevelText->setPosition(m_LevelTextPos);
	m_LevelText->setOrigin(0,0);

	m_Vertices.resize(4);
	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices[0].position	= sf::Vector2f(0.0f, 0.0f);
	m_Vertices[0].color		= sf::Color::White;
	m_Vertices[0].texCoords	= sf::Vector2f(961.0f, 0.0f);

	m_Vertices[1].position	= sf::Vector2f(736.0f, 0.0f);
	m_Vertices[1].color		= sf::Color::White;
	m_Vertices[1].texCoords	= sf::Vector2f(1696.0f, 0.0f);

	m_Vertices[2].position	= sf::Vector2f(736.0f, 768.0f);
	m_Vertices[2].color		= sf::Color::White;
	m_Vertices[2].texCoords	= sf::Vector2f(1696.0f, 767.0f);

	m_Vertices[3].position	= sf::Vector2f(0.0f, 768.0f);
	m_Vertices[3].color		= sf::Color::White;
	m_Vertices[3].texCoords	= sf::Vector2f(961.0f, 767.0f);
	
	m_BGVertices.resize(4);
	m_BGVertices.setPrimitiveType(sf::Quads);
	m_BGVertices[0].position	= sf::Vector2f(58.0f, 57.0f);
	m_BGVertices[0].color		= sf::Color::White;
	m_BGVertices[0].texCoords	= sf::Vector2f(1697.0f, 0.0f);

	m_BGVertices[1].position	= sf::Vector2f(387.0f, 57.0f);
	m_BGVertices[1].color		= sf::Color::White;
	m_BGVertices[1].texCoords	= sf::Vector2f(2025.0f, 0.0f);

	m_BGVertices[2].position	= sf::Vector2f(387.0f,	708.0f);
	m_BGVertices[2].color		= sf::Color::White;
	m_BGVertices[2].texCoords	= sf::Vector2f(2025.0f, 651.0f);

	m_BGVertices[3].position	= sf::Vector2f(58.0f, 708.0f);
	m_BGVertices[3].color		= sf::Color::White;
	m_BGVertices[3].texCoords	= sf::Vector2f(1697.0f, 651.0f);

	m_Piece = CPiece();
	m_NextPiece = CPiece();
	m_NextPiece.SetPosition(sf::Vector2i(0,0));
	unsigned long msgs = MSG_KEYBOARD;
	CSMessageQueue::GetInstance()->RegisterHandler(this, &msgs, 1);
	m_TimeTilMove = MOVETIMEMAX - (int)(48.0f*((float)m_Level/100.0f));
	m_ClearTimer  = CLEARWAIT;
	m_DropTimer   = DROPWAIT; 
	m_ScoreDelay  = SCOREDELAY;
	m_BoardVertices.resize(200*4);
	m_BoardVertices.setPrimitiveType(sf::Quads);
	for(int i = 0; i < 200; i++)
	{
		m_Board[i] = CShape::EShapes::SHAPE_EMPTY;
		SetupBoardVertices(i);
	}
	m_WaitingForNext = false;
	m_WaitForClear = false;
	m_WaitForDrop = false;
	return true;
}

void CMainGameScreen::SetupBoardVertices(unsigned int I)
{
	float x = (float)(I%10);
	float y = (float)((I-x)/10);
	x *= 32;
	y *= 32;
	x += 63;
	y += 62;
	I = I*4;
	if(I >= 200*4)
		return;
	m_BoardVertices[I].position		= sf::Vector2f(x, y);
	m_BoardVertices[I].texCoords	= sf::Vector2f(0, 0);
	m_BoardVertices[I].color		= sf::Color::Transparent;
	m_BoardVertices[I+1].position	= sf::Vector2f(x+32, y);
	m_BoardVertices[I+1].texCoords	= sf::Vector2f(32, 0);
	m_BoardVertices[I+1].color		= sf::Color::Transparent;
	m_BoardVertices[I+2].position	= sf::Vector2f(x+32, y+32);
	m_BoardVertices[I+2].texCoords	= sf::Vector2f(32, 32);
	m_BoardVertices[I+2].color		= sf::Color::Transparent;
	m_BoardVertices[I+3].position	= sf::Vector2f(x, y+32);
	m_BoardVertices[I+3].texCoords	= sf::Vector2f(0, 32);
	m_BoardVertices[I+3].color		= sf::Color::Transparent;
}

bool CMainGameScreen::CheckCollision(sf::Vector2i Pos)
{
	if(Pos.x > 9 || Pos.x < 0 || Pos.y > 19)
			return true;
	if(Pos.y < 0)
		return false;
	int I = (Pos.x+(Pos.y*10));
	return m_Board[I] != CShape::EShapes::SHAPE_EMPTY;
}

void CMainGameScreen::FillSquare(sf::Vector2i Pos, CShape::EShapes Shape)
{ 
	if(Pos.x > 9 || Pos.x < 0 || Pos.y > 19 || Pos.y < 0)
		return;
	int I = (Pos.x+(Pos.y*10));
	sf::Color Col = sf::Color::Transparent;
	m_Board[I] = Shape;
	I *= 4;
	switch(Shape)
	{
		case CShape::EShapes::SHAPE_EMPTY:
			Col = sf::Color::Transparent;
			break;
		case CShape::EShapes::SHAPE_J:
			Col = sf::Color::Red;
			break;
		case CShape::EShapes::SHAPE_L:
			Col = sf::Color::Blue;
			break;
		case CShape::EShapes::SHAPE_O:
			Col = sf::Color::Green;
			break;
		case CShape::EShapes::SHAPE_S:
			Col = sf::Color::Yellow;
			break;
		case CShape::EShapes::SHAPE_I:
			Col = sf::Color::Cyan;
			break;
		case CShape::EShapes::SHAPE_T:
			Col = sf::Color::Color(Orange);
			break;
		case CShape::EShapes::SHAPE_Z:
			Col = sf::Color::Color(Purple);
			break;
		default:
			Col = sf::Color::Color(Gold);
	}
	m_BoardVertices[I].color	 = Col;
	m_BoardVertices[I+1].color	 = Col;
	m_BoardVertices[I+2].color	 = Col;
	m_BoardVertices[I+3].color	 = Col;
}

bool CMainGameScreen::CheckLanded()
{
	sf::Vector2i Pos[4];
	m_Piece.GetPositions(Pos);
	for(int i = 0; i < 4; i++)
	{
		Pos[i].y+=1;
		if(CheckCollision(Pos[i]))
			return true;
	}
	return false;
}

void CMainGameScreen::Land()
{
	sf::Vector2i Pos[4];
	m_Piece.GetPositions(Pos);
	for(int i = 0; i < 4; i++)
	{
		if(Pos[i].y <= -1)
			m_SubState = SS_DEAD;
		FillSquare(Pos[i], m_Piece.GetShape());
	}
	m_WaitingForNext = true;
	CheckLines();
}

bool CMainGameScreen::Update(sf::Time TimeElapsed)
{
	sf::Int32 te = TimeElapsed.asMilliseconds();
	if(m_WaitForClear)
	{
		m_ClearTimer -= te;
		while(m_ClearTimer <= 0)
		{
			ClearLines();
			m_WaitForClear = false;
			m_WaitForDrop = true;
			m_ClearTimer += CLEARWAIT;
		}
	}
	else if(m_WaitForDrop)
	{
		m_DropTimer -= te;
		while(m_DropTimer <= 0)
		{
			if(!DropLines())
				m_WaitForDrop = false;
			m_DropTimer += DROPWAIT;
		}
	}
	else 
	{
		m_DropTimer = DROPWAIT;
		m_ClearTimer = CLEARWAIT;
		m_TimeTilMove -= te;
		while(m_TimeTilMove <= 0)
		{
			if(m_WaitingForNext)
			{
				m_WaitingForNext = false;
				m_Piece = CPiece(m_NextPiece.GetShape());
				m_NextPiece = CPiece();
				m_NextPiece.SetPosition(sf::Vector2i(0,0));
			}
			else
			{
				if(CheckLanded())
					Land();
				else
					m_Piece.MoveDown();
			}
			m_TimeTilMove += MOVETIMEMAX - (int)(48.0f*((float)m_Level/100.0f));;
		}
	}
	if(m_ScoreToAdd != 0)
	{
		m_ScoreDelay -= te;
		while(m_ScoreDelay <= 0)
		{
			m_ScoreDelay += SCOREDELAY;
			m_Score += 1;
			m_ScoreToAdd -= 1;
			std::string str = boost::str(boost::format("%|08|") % (int)m_Score);
			m_ScoreText.reset();
			m_ScoreText = m_Font->CreateText(str, sf::Color::White);
			m_ScoreText->setPosition(m_ScoreTextPos);
				m_ScoreText->setOrigin(0,0);
		}
	}
	ProcessMessages();
	return true;
}

bool CMainGameScreen::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	states.texture = m_GameBoard.get();
	target.draw(m_BGVertices, states);
	states.texture = m_BlockTexture.get();
	target.draw(m_BoardVertices, states);
	if(!m_WaitForClear && !m_WaitingForNext)
		m_Piece.Draw(target, states);
	states.texture = m_GameBoard.get();
	target.draw(m_Vertices, states);
	target.draw(*m_HighscoreText);
	target.draw(*m_ScoreText);
	target.draw(*m_LevelText);
	sf::Vector2f NextPiece(482.0f,483.0f);
	states.transform.translate(NextPiece);
	m_NextPiece.Draw(target, states);
	return true;
}

bool CMainGameScreen::Destroy()
{
	m_GameBoard.reset();
	m_BlockTexture.reset();
	m_HighscoreText.reset();
	m_ScoreText.reset();
	m_LevelText.reset();
	return true;
}