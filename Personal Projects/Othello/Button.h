#pragma once
#include "utility.h"
#include "TextureManager.h"
#include "TextManager.h"
#include <sdl.h>
#include <sdl_gfxprimitives.h>
#include "InputHandler.h"

class Button
{
	protected:
		int ReturnValue;		// The value returned if this button is clicked.

		Pos2D Position;			// The screen position of the button's center.

		Pos2D HalfSize;			// The pre-calculated half-size of the button

		Texture* BtnUp;			// The texture to draw when the button is just... A button
		Texture* BtnOver;		// The texture to draw when the mouse hovers over the button
		Texture* BtnDown;		// The texture to draw when the mouse is down.
		StaticText*  Text;		// The String to draw.
		int TextToDraw;			// Texture to draw, 0, 1 or 2
		float xScale, yScale;	// Scale of the button to be drawn.
		Tint TextColor;
	public:

		bool PosOver(Pos2D Pos); // Is the given position inside the button-area?
		int ButtonPressed(); // Return the return-balue of the button

		Button(); // Create an empty button.
		void Update();
		Button(Pos2D position, std::string Font, std::string label, int Returnvalue); // Create a button

		static Button* CreateButton(Pos2D position, Pos2D size, std::string Font, std::string label, int Returnvalue); // Create a button
		static Button* CreateButton(Pos2D position, Pos2D size, std::string Font, std::string label, int Returnvalue,
									std::string ButtonUp, std::string ButtonOver, std::string ButtonDown, Tint textColor); // Create button from existing textures
		void Draw();

		void Destroy();
};