#ifndef SFMLG_CAPPLICATION_H
#define SFMLG_CAPPLICATION_H
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
#include "CSTextureManager.h"
#include "CSMessageQueue.h"
#include "CSGameStateManager.h"
#include "CSBitmapFontManager.h"
#include "CSAudioManager.h"
#include "CAudioChain.h"
#include "InputMessages.h"
class CApplication
{
	private:
		// Store instance-pointers to the various managers, to allow system-startup initialization.
		CSMessageQueue*		m_MsgQueue;
		CSTextureManager*	m_TextureMgr;
		CSGameStateManager* m_GameStateMgr;
		CSBitmapFontManager* m_BMPFontMgr;
		CSAudioManager*		m_AudioMgr;
		sf::RenderWindow	m_Window;
		bool				m_Running;
		sf::Time			m_Timer;
		sf::Uint16			m_FrameLimit;
	public:
		// Setup the application subsystems.
		bool Initialize();
		
		// Create the window
		bool CreateWindow(sf::String Title, sf::Uint32 Width, sf::Uint32 Height, sf::Uint32 Style, sf::Uint16 FrameLimit=0);
		
		// Starts the gameloop, which keeps running until m_Running is set to false.
		void GameLoop(); 

		// Shut down the system, cleaning up every subsystem running.
		void ShutDown();

};

#endif // SFMLG_CAPPLICATION_H