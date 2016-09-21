#pragma once
#include "Utility.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SDL_GfxPrimitives.h"
#include "TextManager.h"

class CheckBox
{
	private:
		std::string Label;
		bool Checked;
		bool Enabled;
		InputHandler* Input;
		Pos2D Position;
		Texture* Check[4];
		StaticText* Text;
	public:
		CheckBox(void);
		~CheckBox(void);

		static CheckBox* CreateCheckbox(Pos2D position, std::string Font, std::string label, bool checked = false, bool enabled = true);
		bool IsChecked();
		void Update();
		void Draw();
		void Destroy();
		void Enable();
		void Disable();
		bool IsEnabled();
};
