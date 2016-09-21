#include "CMainMenuScreen.h"
#include <boost\format.hpp>
CMainMenuScreen::CMainMenuScreen()
{
	m_StateManager = CSGameStateManager::GetInstance();
}
void CMainMenuScreen::ProcessMessages()
{
	while(!m_MessageQueue.empty())
	{
		MMouseMessage* Msg = (MMouseMessage*)m_MessageQueue.front();
		m_MessageQueue.pop();

		if(Msg->m_EventType == MMouseMessage::MM_BUTTONDOWN)
		{
			int x = Msg->m_MouseEvent.m_ButtonEvent.x;
			int y = Msg->m_MouseEvent.m_ButtonEvent.y;
			if(m_LastBtnStatus == 0)
			{
				if(m_StartBtnRect.contains(x, y))
				{
					m_Vertices[4].texCoords	= sf::Vector2f(736,104);
					m_Vertices[5].texCoords	= sf::Vector2f(960,104);
					m_Vertices[6].texCoords	= sf::Vector2f(960,155);
					m_Vertices[7].texCoords	= sf::Vector2f(736,155);
				}
				else if(m_ExitBtnRect.contains(x, y))
				{
					m_Vertices[8].texCoords	= sf::Vector2f(736,156);
					m_Vertices[9].texCoords	= sf::Vector2f(960,156);
					m_Vertices[10].texCoords= sf::Vector2f(960,207);
					m_Vertices[11].texCoords= sf::Vector2f(736,207);
				}
				else
				{
					m_Vertices[4].texCoords	= sf::Vector2f(736,0);
					m_Vertices[5].texCoords	= sf::Vector2f(960,0);
					m_Vertices[6].texCoords	= sf::Vector2f(960,51);
					m_Vertices[7].texCoords	= sf::Vector2f(736,51);

					m_Vertices[8].texCoords	= sf::Vector2f(736,52);
					m_Vertices[9].texCoords	= sf::Vector2f(960,52);
					m_Vertices[10].texCoords= sf::Vector2f(960,103);
					m_Vertices[11].texCoords= sf::Vector2f(736,103);
				}
				m_LastBtnStatus = 1;
			}
		}
		else if(Msg->m_EventType == MMouseMessage::MM_BUTTONUP)
		{
			int x = Msg->m_MouseEvent.m_ButtonEvent.x;
			int y = Msg->m_MouseEvent.m_ButtonEvent.y;
			if(m_LastBtnStatus == 1)
			{
				m_Vertices[4].texCoords	= sf::Vector2f(736,0);
				m_Vertices[5].texCoords	= sf::Vector2f(960,0);
				m_Vertices[6].texCoords	= sf::Vector2f(960,51);
				m_Vertices[7].texCoords	= sf::Vector2f(736,51);

				m_Vertices[8].texCoords	= sf::Vector2f(736,52);
				m_Vertices[9].texCoords	= sf::Vector2f(960,52);
				m_Vertices[10].texCoords= sf::Vector2f(960,103);
				m_Vertices[11].texCoords= sf::Vector2f(736,103);
				m_LastBtnStatus = 0;
				if(m_StartBtnRect.contains(x, y))
				{
					CMainGameScreen* mainGameScreen = new CMainGameScreen(m_Level);
					m_StateManager->PushState(mainGameScreen);
					//m_SubState = SS_DEAD;
				}
				else if(m_ExitBtnRect.contains(x, y))
				{
					m_Exit = true;
				}
				else if(m_UpBtnRect.contains(x, y))
				{
					if(m_Level < 100)
					{
						m_Level++;
						std::string str = boost::str(boost::format("Difficulty Level: %|03|") % (int)m_Level);
						m_Text.reset();
						m_Text = CSBitmapFontManager::GetInstance()->GetFont("Font")->CreateText(str, sf::Color::White);
						m_Text->setOrigin(0,0);
						m_Text->setPosition(m_TextX, m_TextY);
					}
				}
				else if(m_DownBtnRect.contains(x, y))
				{
					if(m_Level > 1)
					{
						m_Level--;
						std::string str = boost::str(boost::format("Difficulty Level: %|03|") % (int)m_Level);
						m_Text.reset();
						m_Text = CSBitmapFontManager::GetInstance()->GetFont("Font")->CreateText(str, sf::Color::White);
						m_Text->setOrigin(0,0);
						m_Text->setPosition(m_TextX, m_TextY);
					}
				}
			}
		}
		else if(Msg->m_EventType == MMouseMessage::MM_MOVE)
		{
			int x = Msg->m_MouseEvent.m_MoveEvent.x;
			int y = Msg->m_MouseEvent.m_MoveEvent.y;
			if(m_StartBtnRect.contains(x, y))
			{
				m_Vertices[4].color = sf::Color::Yellow;
				m_Vertices[5].color = sf::Color::Yellow;
				m_Vertices[6].color = sf::Color::Yellow;
				m_Vertices[7].color = sf::Color::Yellow;

				m_Vertices[8].color = sf::Color::White;
				m_Vertices[9].color = sf::Color::White;
				m_Vertices[10].color = sf::Color::White;
				m_Vertices[11].color = sf::Color::White;
			}
			else if(m_ExitBtnRect.contains(x, y))
			{
				m_Vertices[4].color = sf::Color::White;
				m_Vertices[5].color = sf::Color::White;
				m_Vertices[6].color = sf::Color::White;
				m_Vertices[7].color = sf::Color::White;

				m_Vertices[8].color = sf::Color::Yellow;
				m_Vertices[9].color = sf::Color::Yellow;
				m_Vertices[10].color = sf::Color::Yellow;
				m_Vertices[11].color = sf::Color::Yellow;
			}
			else
			{
				m_Vertices[4].color = sf::Color::White;
				m_Vertices[5].color = sf::Color::White;
				m_Vertices[6].color = sf::Color::White;
				m_Vertices[7].color = sf::Color::White;

				m_Vertices[8].color = sf::Color::White;
				m_Vertices[9].color = sf::Color::White;
				m_Vertices[10].color = sf::Color::White;
				m_Vertices[11].color = sf::Color::White;
			}
		}

		delete Msg;
	}
}

bool CMainMenuScreen::Initialize()
{
	m_Vertices.setPrimitiveType(sf::Quads);
	m_Vertices.resize(20);
	// Main background
	m_Vertices[0].position	= sf::Vector2f(0,0);
	m_Vertices[0].color		= sf::Color::White;
	m_Vertices[0].texCoords	= sf::Vector2f(0,0);

	m_Vertices[1].position	= sf::Vector2f(735,0);
	m_Vertices[1].color		= sf::Color::White;
	m_Vertices[1].texCoords	= sf::Vector2f(735,0);

	m_Vertices[2].position	= sf::Vector2f(735,767);
	m_Vertices[2].color		= sf::Color::White;
	m_Vertices[2].texCoords	= sf::Vector2f(735,767);

	m_Vertices[3].position	= sf::Vector2f(0,767);
	m_Vertices[3].color		= sf::Color::White;
	m_Vertices[3].texCoords	= sf::Vector2f(0,767);
	// Start Button
	m_Vertices[4].position	= sf::Vector2f(255,243);
	m_Vertices[4].color		= sf::Color::White;
	m_Vertices[4].texCoords	= sf::Vector2f(736,0);

	m_Vertices[5].position	= sf::Vector2f(479,243);
	m_Vertices[5].color		= sf::Color::White;
	m_Vertices[5].texCoords	= sf::Vector2f(960,0);
	
	m_Vertices[6].position	= sf::Vector2f(479,295);
	m_Vertices[6].color		= sf::Color::White;
	m_Vertices[6].texCoords	= sf::Vector2f(960,51);
	
	m_Vertices[7].position	= sf::Vector2f(255,295);
	m_Vertices[7].color		= sf::Color::White;
	m_Vertices[7].texCoords	= sf::Vector2f(736,51);

	m_StartBtnRect = sf::IntRect(255, 243, 224, 52);
	// Exit Button.
	m_Vertices[8].position	= sf::Vector2f(255,305);
	m_Vertices[8].color		= sf::Color::White;
	m_Vertices[8].texCoords	= sf::Vector2f(736,52);
	
	m_Vertices[9].position	= sf::Vector2f(479,305);
	m_Vertices[9].color		= sf::Color::White;
	m_Vertices[9].texCoords	= sf::Vector2f(960,52);
	
	m_Vertices[10].position	= sf::Vector2f(479,357);
	m_Vertices[10].color	= sf::Color::White;
	m_Vertices[10].texCoords= sf::Vector2f(960,103);
	
	m_Vertices[11].position	= sf::Vector2f(255,357);
	m_Vertices[11].color	= sf::Color::White;
	m_Vertices[11].texCoords= sf::Vector2f(736,103);
	

	m_ExitBtnRect = sf::IntRect(255, 305, 224, 52);

	// Level-up arrow
	m_Vertices[12].position	= sf::Vector2f(331,367);
	m_Vertices[12].color	= sf::Color::White;
	m_Vertices[12].texCoords= sf::Vector2f(736,209);
	
	m_Vertices[13].position	= sf::Vector2f(363,367);
	m_Vertices[13].color	= sf::Color::White;
	m_Vertices[13].texCoords= sf::Vector2f(768,209);
	
	m_Vertices[14].position	= sf::Vector2f(363,399);
	m_Vertices[14].color	= sf::Color::White;
	m_Vertices[14].texCoords= sf::Vector2f(768,241);
	
	m_Vertices[15].position	= sf::Vector2f(331,399);
	m_Vertices[15].color	= sf::Color::White;
	m_Vertices[15].texCoords= sf::Vector2f(736,241);

	m_UpBtnRect = sf::IntRect(331, 367, 32, 32);

	// Level-down arrow

	m_Vertices[16].position	= sf::Vector2f(365,367);
	m_Vertices[16].color	= sf::Color::White;
	m_Vertices[16].texCoords= sf::Vector2f(769,209);
	
	m_Vertices[17].position	= sf::Vector2f(397,367);
	m_Vertices[17].color	= sf::Color::White;
	m_Vertices[17].texCoords= sf::Vector2f(801,209);
	
	m_Vertices[18].position	= sf::Vector2f(397,399);
	m_Vertices[18].color	= sf::Color::White;
	m_Vertices[18].texCoords= sf::Vector2f(801,241);
	
	m_Vertices[19].position	= sf::Vector2f(365,399);
	m_Vertices[19].color	= sf::Color::White;
	m_Vertices[19].texCoords= sf::Vector2f(769,241);

	m_DownBtnRect = sf::IntRect(365, 367, 32, 32);
	
	m_Texture = CSTextureManager::GetInstance()->GetTexture("GameBoard");

	m_SubState = SS_TRANSITION_IN;
	unsigned long msg = MSG_MOUSE;
	CSMessageQueue::GetInstance()->RegisterHandler(this, &msg, 1);
	m_Exit = false;
	m_LastBtnStatus = 0;
	m_Level = 1;
	m_Text = CSBitmapFontManager::GetInstance()->GetFont("Font")->CreateText("Difficulty Level: 001\0", sf::Color::White);
	sf::IntRect ir (CSBitmapFontManager::GetInstance()->GetFont("Font")->GetStringBoundaries("Difficulty Level: 001\0"));
	m_TextX = float(383 - (ir.width  - ir.left)/2);
	m_TextY = float(399 + (ir.height - ir.top)/2 + 2);
	m_Text->setOrigin(0,0);
	m_Text->setPosition(m_TextX,m_TextY);
	return true;
}

bool CMainMenuScreen::Update(sf::Time TimeElapsed)
{
	ProcessMessages();
	return (!m_Exit);
}

bool CMainMenuScreen::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	states.texture = m_Texture.get();
	target.draw(m_Vertices, states);
	target.draw((*m_Text));
	return true;
}

bool CMainMenuScreen::Destroy()
{
	m_Texture.reset();
	return true;
}