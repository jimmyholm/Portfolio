#pragma once

#include <sdl.h>
#include "utility.h"

#define MOUSE_LEFT		1
#define MOUSE_RIGHT		2
#define MOUSE_MIDDLE	4
#define KEYLIMIT		(Uint8)-1

class InputHandler
{
	private:
		static InputHandler* Instance; // Singleton instance
		
		SDL_Event e;
		Uint32 LastUpdate;
		Uint8 Keys[SDLK_LAST];
		Uint8 LastKeys[SDLK_LAST];
		bool Wheel;
		Pos2D MousePosition;
		bool Shift;
		bool LastShift;
		bool Ctrl;
		bool LastCtrl;
		bool Alt;
		bool LastAlt;
		bool capsLock;
		Uint8 Button;
		Uint8 LastButton;
		Uint32 DoubleClickInterval; // The maximum time to wait for a double-click.
		Uint32 LastClick;			// The last Tick the mouse was clicked
		Uint8  LastButtonClicked;	// The last mouse-button clicked
		Uint8  ButtonDoubled;		// The button(s) that's been double clicked.
		bool CheckDouble;			// Put this to true when the mouse is clicked,
									// and then falsify it if LastClick - Tick is greater than DoubleClickInterval.

		InputHandler();

	public:

		static InputHandler* GetInstance();
		
		void Setup();
		void OneFrame(Uint32 Tick); // Update the input
		bool CapsLock();
		bool KeyHeld(SDLKey key);
		bool KeyDown(SDLKey key);
		bool KeyUp(SDLKey key);
		bool MouseDown(Uint8 button);
		bool MouseHeld(Uint8 button);
		bool MouseUp(Uint8 button);
		bool MouseWheelMove();
		bool AnyKey();
		bool ShiftHeld();
		bool ShiftDown();
		bool ShiftUp();
		bool CtrlHeld();
		bool CtrlDown();
		bool CtrlUp();
		bool AltHeld();
		bool AltDown();
		bool AltUp();
		bool DoubleClick(Uint8 button);
		void Reset(); // Clear all the input-states
		Pos2D GetMousePosition();
		void Destroy();
};