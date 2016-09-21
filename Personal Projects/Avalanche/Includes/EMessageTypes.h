#ifndef SFMLG_EMESSAGETYPES_H
#define SFMLG_EMESSAGETYPES_H

enum eMessageTypes
{
	// Input messages
	MSG_KEYBOARD = 1,
	MSG_MOUSE,
	MSG_JOYSTICK,
	// Action-message, used by the input-system to transform an input to an action for the game system.
	MSG_ACTION
};

#endif // SFMLG_EMESSAGETYPES_H