#include "InputHandler.h"

InputHandler* InputHandler::Instance = 0;

InputHandler* InputHandler::GetInstance()
{
	if(Instance == 0)
		Instance = new InputHandler;
	return Instance;	
}

InputHandler::InputHandler() :  Shift(false), LastShift(false), Ctrl(false), LastCtrl(false),
								Alt(false), LastAlt(false), CheckDouble(false),	DoubleClickInterval(200),
								LastButtonClicked(0), Wheel(false), MousePosition(Pos2D()), 
								LastUpdate(0), Button(false), LastButton(false), ButtonDoubled(0), capsLock(false)
{
	memset(Keys, 0, sizeof(Uint8)*SDLK_LAST);
	memset(LastKeys, 0, sizeof(Uint8)*SDLK_LAST);
}

void InputHandler::Setup()
{

}

void InputHandler::OneFrame(Uint32 Tick)
{
	if(LastClick > Tick)
		LastClick = 0;
	if(LastClick != 0 && Tick - LastClick >= DoubleClickInterval)
	{
  		LastClick = 0;
		CheckDouble = 0;
		LastButtonClicked = 0;
		ButtonDoubled = 0;
	}
	memcpy(LastKeys, Keys, sizeof(Uint8)*SDLK_LAST);
	memcpy(Keys, SDL_GetKeyState(0), sizeof(Uint8)*SDLK_LAST);
	Uint16 ModState= SDL_GetModState();
	capsLock = false;
	LastShift = Shift;
	Shift = (ModState & KMOD_SHIFT) != 0;
	LastCtrl = Ctrl;
	Ctrl = (ModState & KMOD_CTRL) != 0;
	LastAlt = Alt;
	Alt = (ModState & KMOD_ALT) != 0;
	capsLock = (ModState & KMOD_CAPS) != 0;
	ButtonDoubled = 0;
	LastButton = Button;
	int x = 0, y = 0;
	Button = SDL_GetMouseState(&x, &y);
	MousePosition = Pos2D((float)x, (float)y);
	if(Button != 0 && LastClick == 0)
	{
		LastClick = Tick;
		CheckDouble = true;
		LastButtonClicked = Button;
	}
	else if(Button != 0 && Button != LastButton && Tick - LastClick > 100 && CheckDouble)
	{
		if((Button & LastButtonClicked) > 0)
		{
			ButtonDoubled = LastButtonClicked;
			LastClick = 0;
			CheckDouble = 0;
			LastButtonClicked = 0;
		}
	}
}

bool InputHandler::KeyHeld(SDLKey key)
{
	return Keys[(int)key] != 0;
}

bool InputHandler::KeyDown(SDLKey key)
{
	return (Keys[(int)key]!= 0) && (LastKeys[(int)key] == 0);
}

bool InputHandler::KeyUp(SDLKey key)
{
	return (Keys[(int)key] == 0) && (LastKeys[(int)key]!= 0);
}

bool InputHandler::ShiftHeld()
{
	return (Shift != 0);
}
bool InputHandler::ShiftDown()
{
	return (Shift) && !(LastShift);
}

bool InputHandler::ShiftUp()
{
	return !(Shift) && (LastShift);
}

bool InputHandler::CtrlHeld()
{
	return (Ctrl != 0);
}
bool InputHandler::CtrlDown()
{
	return (Ctrl) && !(LastCtrl);
}

bool InputHandler::CtrlUp()
{
	return !(Ctrl) && (LastCtrl);
}

bool InputHandler::AltHeld()
{
	return (Alt != 0);
}
bool InputHandler::AltDown()
{
	return (Alt) && !(LastAlt);
}

bool InputHandler::AltUp()
{
	return !(Alt) && (LastAlt);
}

bool InputHandler::AnyKey()
{
	for(int i = (int)SDLK_FIRST; i < (int)SDLK_LAST; i++)
	{
		if(KeyDown((SDLKey)i))
			return true;
	}
	return false;
}


Pos2D InputHandler::GetMousePosition()
{
	return MousePosition;
}

bool InputHandler::MouseDown(Uint8 button)
{
	return ((Button & button) > 0 && (LastButton & button) == 0);
}

bool InputHandler::MouseUp(Uint8 button)
{
	return ((Button & button) == 0 && (LastButton & button) > 0);
}

bool InputHandler::MouseHeld(Uint8 button)
{
	return (Button & button) != 0;
}

bool InputHandler::MouseWheelMove()
{
	return Wheel == true;
}

bool InputHandler::DoubleClick(Uint8 button)
{
	return (ButtonDoubled & button) > 0;
}


void InputHandler::Reset()
{
	memset(LastKeys, false, sizeof(Uint8)*SDLK_LAST);
}

bool InputHandler::CapsLock()
{
	return capsLock;
}
void InputHandler::Destroy()
{
	delete InputHandler::Instance;
}