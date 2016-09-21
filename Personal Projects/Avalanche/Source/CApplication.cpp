#include "CApplication.h"
#include "CBitmapFont.h"
#include "CIntroScreen.h"
#include <boost/format.hpp>
bool CApplication::Initialize()
{
	m_MsgQueue = CSMessageQueue::GetInstance();
	m_TextureMgr = CSTextureManager::GetInstance();
	m_GameStateMgr = CSGameStateManager::GetInstance();
	m_BMPFontMgr = CSBitmapFontManager::GetInstance();
	m_AudioMgr = CSAudioManager::GetInstance();
	CIntroScreen* intro = new CIntroScreen();
	m_GameStateMgr->PushState(intro);
	intro->Initialize();
	m_Running = true;
	return true;
}

bool CApplication::CreateWindow(sf::String Title, sf::Uint32 Width, sf::Uint32 Height, sf::Uint32 Style, sf::Uint16 FrameLimit)
{
	m_Window.create(sf::VideoMode(Width, Height, 32), Title, Style);
	if(!m_Window.isOpen())
	{
		throw std::exception("Failed to create window!");
		return false;
	}
	m_FrameLimit = FrameLimit;
	return true;
}

void CApplication::GameLoop()
{
	sf::Clock timeElapsed;
	timeElapsed.restart();
	MKeyboardMessage* KMsg;
	MMouseMessage*	  MMsg;
	sf::Time elapsed;
	bool closed = false;
	while(m_Running)
	{
		sf::Event event;
		while(m_Window.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					m_Window.close();
					closed = true;
					continue;
				case sf::Event::KeyPressed:
					KMsg = new MKeyboardMessage();
					KMsg->m_KeyState = MKeyboardMessage::KM_PRESSED;
					KMsg->m_KeyEvent = event.key;
					m_MsgQueue->PostMessage(KMsg);
					break;
				case sf::Event::KeyReleased:
					KMsg = new MKeyboardMessage();
					KMsg->m_KeyState = MKeyboardMessage::KM_RELEASED;
					KMsg->m_KeyEvent = event.key;
					m_MsgQueue->PostMessage(KMsg);
					break;
				case sf::Event::MouseMoved:
					MMsg = new MMouseMessage();
					MMsg->m_EventType = MMouseMessage::MM_MOVE;
					MMsg->m_MouseEvent.m_MoveEvent = event.mouseMove;
					m_MsgQueue->PostMessage(MMsg);
					break;
				case sf::Event::MouseButtonPressed:
					MMsg = new MMouseMessage();
					MMsg->m_EventType = MMouseMessage::MM_BUTTONDOWN;
					MMsg->m_MouseEvent.m_ButtonEvent = event.mouseButton;
					m_MsgQueue->PostMessage(MMsg);
					break;
				case sf::Event::MouseButtonReleased:
					MMsg = new MMouseMessage();
					MMsg->m_EventType = MMouseMessage::MM_BUTTONUP;
					MMsg->m_MouseEvent.m_ButtonEvent = event.mouseButton;
					m_MsgQueue->PostMessage(MMsg);
					break;
				case sf::Event::MouseWheelMoved:
					MMsg = new MMouseMessage();
					MMsg->m_EventType = MMouseMessage::MM_WHEEL;
					MMsg->m_MouseEvent.m_WheelEvent = event.mouseWheel;
					m_MsgQueue->PostMessage(MMsg);
					break;
			}
		}
		if(closed)
		{
			m_Running = false;
			continue;
		}
		elapsed = timeElapsed.restart();
		m_MsgQueue->DispatchMessages();
		
		m_Running = m_GameStateMgr->Update(elapsed);
		m_Window.clear();
		m_GameStateMgr->Draw(m_Window, sf::RenderStates::Default);
		m_Window.display();
		if(m_FrameLimit != 0)
		{
			if(elapsed.asMilliseconds() < 1000/m_FrameLimit)
			{
				sf::Int32 sleepTime = (1000/m_FrameLimit) - elapsed.asMilliseconds();
				sf::sleep(sf::milliseconds(sleepTime));
				std::cout << "Sleeping for " << sleepTime << " ms" << std::endl;
			}
		}
	}
}

void CApplication::ShutDown()
{
	m_MsgQueue->Clear();
	m_MsgQueue = NULL;
	m_TextureMgr->Clear();
	m_TextureMgr = NULL;
	m_BMPFontMgr->Clear();
	m_BMPFontMgr = NULL;
	m_AudioMgr->Clear();
	m_AudioMgr = NULL;
}