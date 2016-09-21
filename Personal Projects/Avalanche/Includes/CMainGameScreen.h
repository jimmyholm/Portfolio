#ifndef SFMLG_CMAINGAMESCREEN_H
#define SFMLG_CMAINGAMESCREEN_H
#include "IGameState.h"
#include "CSTextureManager.h"
#include "CSBitmapFontManager.h"
#include "CMainMenuScreen.h"
#include "Pieces.h"

#define MOVETIMEMAX 25
#define CLEARWAIT	20
#define DROPWAIT	10
#define SCOREDELAY	1
#define PAUSE_STATE 10
#define GAMEOVER_STATE 11
class CMainGameScreen : public IGameState
{
	protected:
		char			m_Level;
		unsigned int	m_Score;
		unsigned int	m_HighScore;
		TEXPTR			m_BlockTexture;
		TEXPTR			m_GameBoard;
		BMPFONTPTR		m_Font;
		BMPTEXTPTR		m_ScoreText;
		BMPTEXTPTR		m_AddScore;
		BMPTEXTPTR		m_HighscoreText;
		BMPTEXTPTR		m_LevelText;
		BMPTEXTPTR		m_ScoreAddText;
		CPiece			m_NextPiece;
		sf::Int32		m_TimeTilMove;
		CPiece			m_Piece;
		CSTextureManager* m_TexMgr;
		sf::VertexArray m_Vertices;
		sf::VertexArray m_BGVertices;
		sf::VertexArray m_BoardVertices;
		sf::Vector2f	m_ScoreTextPos;
		sf::Vector2f	m_HighscoreTextPos;
		sf::Vector2f	m_LevelTextPos;
		CShape::EShapes	m_Board[200];
		bool			m_WaitingForNext;
		unsigned int	m_ScoreToAdd;
		bool			m_WaitForClear;
		bool			m_WaitForDrop;
		sf::Int32		m_ClearTimer;
		sf::Int32		m_DropTimer;
		sf::Int32		m_ScoreDelay;

		void			ProcessMessages();
		void			CheckLines();
		void			ClearLines();
		void			DropLine(unsigned int y);
		bool			EmptyLine(unsigned int y);
		bool			FullLine(unsigned int y);
		void			MarkLine(unsigned int y);
		bool			DropLines();
		void			AddScore();
		void			EndGame();
		void			FillSquare(sf::Vector2i Pos, CShape::EShapes Shape);
		void			SetupBoardVertices(unsigned int I);
		bool			CheckCollision(sf::Vector2i Pos);
		bool			CheckLanded();
		void			Land();
	public:

		CMainGameScreen(char Level);
		bool Initialize();
		bool Update(sf::Time TimeElapsed);
		bool Draw(sf::RenderTarget& target, sf::RenderStates states);
		bool Destroy();
};

#endif