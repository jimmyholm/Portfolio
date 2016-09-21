#ifndef SFMLG_CINTROSCREEN_H
#define SFMLG_CINTROSCREEN_H
#include "CSMessageQueue.h"
#include "IGameState.h"
#include "CSTextureManager.h"
#include "CMainMenuScreen.h"
#include "CSGameStateManager.h"

class CIntroScreen : public IGameState
{
	protected:
		void ProcessMessages();
		sf::Texture* m_Active;
		sf::Texture* m_Senilica;
		sf::Texture* m_Sfml;
		char		 m_State;
		bool		 m_CloseEarly;
		sf::VertexArray m_Vertices;
		sf::Time	 m_Timer;
	public:
		CIntroScreen();
		bool Initialize();
		bool Update(sf::Time TimeElapsed);
		bool Draw(sf::RenderTarget& target, sf::RenderStates states);
		bool Destroy();
};
#endif