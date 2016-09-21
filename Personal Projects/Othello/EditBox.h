#pragma once
#include "Utility.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include <SDL.h>
#include <string>
#include "TextManager.h"

#define CEDIT_ALLOW_NUMBERS			1
#define CEDIT_ALLOW_TEXT			2
#define CEDIT_ALLOW_SPECIAL			4
#define CEDIT_ALLOW_KEYPADNUMBERS	8
#define CEDIT_ALLOW_FULLKEYPAD		CEDIT_ALLOW_SPECIAL|CEDIT_ALLOW_KEYPADNUMBERS
#define CEDIT_ALLOW_NUMBERICALS		CEDIT_ALLOW_NUMBERS|CEDIT_ALLOW_KEYPADNUMBERS
#define CEDIT_ALLOW_ALL				CEDIT_ALLOW_NUMBERS | CEDIT_ALLOW_TEXT | CEDIT_ALLOW_SPECIAL | CEDIT_ALLOW_FULLKEYPAD


class EditBox
{
	private:
		std::string String;
		size_t		StrPos;
		Pos2D		Position;
		Pos2D		Size;
		bool		Focus;
		InputHandler* Input;
		Texture*	texture;
		std::string font;
		int			MaxLength;
		bool		Enabled;
		EditBox();
		int Flags;
		void Init();
		bool Flash;
		int FlashTimer;
		int RepeatTimer;
		int RepeatThreshhold;
		float xScale, yScale;
		int xPadding, yPadding;
	public:
		~EditBox();
		static EditBox* CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, int flags = CEDIT_ALLOW_ALL, int maxLength = 0, bool enabled = true);
		static EditBox* CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, std::string Graphics, Pos2D Padding, int flags = CEDIT_ALLOW_ALL, int maxLength = 0, bool enabled = true);
		static EditBox* CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, Texture* Graphics, Pos2D Padding, int flags = CEDIT_ALLOW_ALL, int maxLength = 0, bool enabled = true);

		void Update(Uint32 TickDelta);
		std::string GetString();
		void Draw();
		void Destroy();
		bool HasFocus();
		void GiveFocus(bool focus);
		void SetFlags(int flag);
		int GetFlags();
		void Enable();
		void Disable();
		bool IsEnabled();
};
