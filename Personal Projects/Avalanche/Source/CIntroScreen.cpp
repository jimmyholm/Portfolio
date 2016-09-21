#include "CIntroScreen.h"
#include "InputMessages.h"

CIntroScreen::CIntroScreen()
{
	m_StateManager = CSGameStateManager::GetInstance();
}

void CIntroScreen::ProcessMessages()
{
	while(!m_MessageQueue.empty())
	{
		MKeyboardMessage* Msg = reinterpret_cast<MKeyboardMessage*>(m_MessageQueue.front());
		if(Msg->m_KeyState == MKeyboardMessage::KM_RELEASED)
		{
			if(Msg->m_KeyEvent.code == sf::Keyboard::Escape)
			{
				m_SubState = SS_DEAD;
				m_StateManager->PushState(new CMainMenuScreen);
			}
		}
		m_MessageQueue.pop();
	}
}

bool CIntroScreen::Initialize()
{
	unsigned long msgs = MSG_KEYBOARD;
	CSMessageQueue::GetInstance()->RegisterHandler(this, &msgs, 1);
	m_Senilica = new sf::Texture();
	m_Senilica->loadFromFile("Resources\\Textures\\senilicalogo.png");
	m_Sfml = new sf::Texture();
	m_Sfml->loadFromFile("Resources\\Textures\\sfml-logo-small.tga");
	// Insert the main-menu screen into the state-manager.
	m_SubState = SS_ACTIVE;
	m_State = 0;
	m_Active = m_Senilica;
	m_Vertices = sf::VertexArray(sf::Quads, 4);
	m_Vertices[0].position = sf::Vector2f(112.0f,128.0f);
	m_Vertices[0].texCoords = sf::Vector2f(0,0);
	m_Vertices[1].position = sf::Vector2f(624.0f,128.0f);
	m_Vertices[1].texCoords = sf::Vector2f(512,0);
	m_Vertices[2].position = sf::Vector2f(624.0f,640.0f);
	m_Vertices[2].texCoords = sf::Vector2f(512,512);
	m_Vertices[3].position = sf::Vector2f(112.0f,640.0f);
	m_Vertices[3].texCoords = sf::Vector2f(0,512);

	for(int i = 0; i < 4; i++)
	{
		m_Vertices[i].color = sf::Color(255,255,255,0);
	}
	CSTextureManager::GetInstance()->LoadTexture("GameBoard", "Resources\\Textures\\gameboard.tga");
	CSTextureManager::GetInstance()->LoadTexture("Font", "Resources\\Textures\\font.tga");
	CSTextureManager::GetInstance()->LoadTexture("Block", "Resources\\Textures\\block.tga");
	CSBitmapFontManager::GetInstance()->LoadFont("Resources\\font.xml", "Font");
	return true;
}

/*
Vertex positions for textures, top-left and bottom-right.
Sentient Silica Logo (512x512):

112,128		624,640

SFML logo (512x256):
112,256		624,512

*/


bool CIntroScreen::Update(sf::Time TimeElapsed)
{
	ProcessMessages();
	m_Timer += TimeElapsed;
	sf::Uint8 alpha = 0;
	switch(m_State)
	{
		case 0: // Fade-in Senilica logo
			if(m_Timer.asSeconds() < 1.5f)
				 alpha = sf::Uint8(((m_Timer.asSeconds() / 1.5f) * 255.0f));
			else
			{
				alpha = 255;
				m_State = 1;
				m_Timer = sf::Time::Zero;
			}
			for(int i = 0; i < 4; i++)
			{
				m_Vertices[i].color = sf::Color(255,255,255,alpha);
			}
			break;
		case 1: // Show Senilica logo
			if(m_Timer.asSeconds() >= 2.0f)
			{
				m_Timer = sf::Time::Zero;
				m_State = 2;
			}
			break;
		case 2: // Fade out Senilica logo
			if(m_Timer.asSeconds() < 1.5f)
				 alpha = 255 - sf::Uint8(((m_Timer.asSeconds() / 1.5f) * 255.0f));
			else
			{
				alpha = 0;
				m_State = 3;
				m_Timer = sf::Time::Zero;
				m_Active = m_Sfml;
				m_Vertices[0].position  = sf::Vector2f(112.0f, 256.0f);
				m_Vertices[1].position  = sf::Vector2f(624.0f, 256.0f);
				m_Vertices[2].position  = sf::Vector2f(624.0f, 512.0f);
				m_Vertices[2].texCoords = sf::Vector2f(512.0f, 256.0f);
				m_Vertices[3].position  = sf::Vector2f(112.0f, 512.0f);
				m_Vertices[3].texCoords = sf::Vector2f(0.0f, 256.0f);
			}
			for(int i = 0; i < 4; i++)
			{
				m_Vertices[i].color = sf::Color(255,255,255,alpha);
			}
			break;
		case 3: // Fade in SFML logo
			if(m_Timer.asSeconds() < 1.5f)
				 alpha = sf::Uint8(((m_Timer.asSeconds() / 1.5f) * 255.0f));
			else
			{
				alpha = 255;
				m_State = 4;
				m_Timer = sf::Time::Zero;
			}
			for(int i = 0; i < 4; i++)
			{
				m_Vertices[i].color = sf::Color(255,255,255,alpha);
			}
			break;
		case 4: // Show SFML logo.
			if(m_Timer.asSeconds() >= 2.0f)
			{
				m_Timer = sf::Time::Zero;
				m_State = 5;
			}
			break;
		case 5: // Fade out SFML logo.
			if(m_Timer.asSeconds() < 1.5f)
				 alpha = 255 - sf::Uint8(((m_Timer.asSeconds() / 1.5f) * 255.0f));
			else
			{
				m_SubState = SS_DEAD;
				m_StateManager->PushState(new CMainMenuScreen);
			}
			for(int i = 0; i < 4; i++)
			{
				m_Vertices[i].color = sf::Color(255,255,255,alpha);
			}
			break;
	}
	return true;
}

bool CIntroScreen::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	states.texture = m_Active;
	target.draw(m_Vertices, states);
	return true;
}

bool CIntroScreen::Destroy()
{
	unsigned long Messages = MSG_KEYBOARD;
	CSMessageQueue::GetInstance()->RemoveHandler(&Messages, 1);
	m_Active = NULL;
	delete m_Senilica;
	delete m_Sfml;
	return true;
}