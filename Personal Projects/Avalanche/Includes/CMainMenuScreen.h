#ifndef SFMLG_CMAINMENUSCREEN_H
#define SFMLG_CMAINMENUSCREEN_H
#include <SFML\Graphics.hpp>
#include "CSGameStateManager.h"
#include "IGameState.h"
#include "InputMessages.h"
#include "CSTextureManager.h"
#include "CSMessageQueue.h"
#include "CSBitmapFontManager.h"
#include "CMainGameScreen.h"

class CMainMenuScreen : public IGameState
{
	protected:
		TEXPTR				m_Texture;
		sf::VertexArray		m_Vertices;
		sf::IntRect			m_StartBtnRect;
		sf::IntRect			m_ExitBtnRect;
		sf::IntRect			m_UpBtnRect;
		sf::IntRect			m_DownBtnRect;
		BMPTEXTPTR			m_Text;
		char				m_Level;
		char				m_BtnStatus;		// 0 = none, 1 = start game, 2 = exit game
		char				m_LastBtnStatus;
		bool				m_Exit;
		float				m_TextX;
		float				m_TextY;
		void				ProcessMessages();
	public:
		CMainMenuScreen();
		bool Initialize();
		bool Update(sf::Time TimeElapsed);
		bool Draw(sf::RenderTarget& target, sf::RenderStates states);
		bool Destroy();
};

#endif