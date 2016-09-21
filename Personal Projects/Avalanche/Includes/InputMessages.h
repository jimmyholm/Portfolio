#ifndef SFMLG_INPUTMESSAGES_H
#define SFMLG_INPUTMESSAGES_H
#include "SFML\Window\Keyboard.hpp"
#include "SFML\Window\Mouse.hpp"
#include "SFML\Window\Event.hpp"
#include "IMessage.h"

class MKeyboardMessage : public IMessage
{
	public:
		enum keyboardState
		{
			KM_PRESSED  = 0,
			KM_RELEASED = 1
		};
		MKeyboardMessage() {m_MessageType = MSG_KEYBOARD;}
		keyboardState m_KeyState;
		sf::Event::KeyEvent m_KeyEvent;
};

class MMouseMessage : public IMessage
{
	public:
		enum mouseEventType
		{
			MM_BUTTONDOWN = 0,
			MM_BUTTONUP,
			MM_MOVE,
			MM_WHEEL
		};
		MMouseMessage() { m_MessageType = MSG_MOUSE;}
		mouseEventType m_EventType;
		union
		{
			sf::Event::MouseButtonEvent m_ButtonEvent;
			sf::Event::MouseMoveEvent	m_MoveEvent;
			sf::Event::MouseWheelEvent  m_WheelEvent;
		} m_MouseEvent;
};


#endif