#pragma once
#include "InputHandler.h"
#include "TextureManager.h"
class GameScreenManager;
class GameScreen
{
	protected:
		InputHandler*		Input;
		GameScreenManager*	ScreenMgr;
	public:
		virtual bool Update(Uint32 TickDelta) = 0; // Return false if this screen should be popped
		virtual void Draw() = 0;
		virtual void Destroy() = 0; // De-initialize the screem; called when the screen is popped
};