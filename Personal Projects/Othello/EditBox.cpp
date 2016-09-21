#include "EditBox.h"

EditBox::EditBox(void) : String(""), StrPos(0), Position(Pos2D(0, 0)), Size(Pos2D(0,0)), Focus(false), Enabled(true)
{
	Input = InputHandler::GetInstance();
	RepeatThreshhold = 150;
	RepeatTimer = 0;
}

EditBox::~EditBox(void)
{
}

void EditBox::Init()
{
	texture = new Texture;
	SDL_Surface* srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, (int)Size.x, (int)Size.y,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, (Sint16)Size.x-1, (Sint16)Size.y-1, 0, 0, 0, 0xFF);
	boxRGBA(srf, 1, 1, (Sint16)Size.x-2, (Sint16)Size.y-2, 0xFF, 0xFF, 0xFF, 0xFF);
	texture->TextureFromSurface(srf);
	xScale = 1.0f;
	yScale = 1.0f;
}

EditBox* EditBox::CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, int flags, int maxLength, bool enabled)
{
	EditBox* ret = new EditBox;
	ret->Position = pos;
	ret->Size = size;
	ret->Size.y = (float)TextManager::GetInstance()->GetFontHeight(Font)+4;
	ret->String = defString;
	ret->Flags = flags;
	ret->font = Font;
	ret->MaxLength = maxLength;
	ret->Enabled = enabled;
	if(ret->Size.y == 0)
	{
		delete ret;
		ret = NULL;
	}
	else
		ret->Init();
	return ret;
}
EditBox* EditBox::CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, std::string Graphics, Pos2D Padding, int flags, int maxLength, bool enabled)
{
	EditBox* ret = new EditBox;
	ret->Position = pos;
	ret->Size = size;
	ret->Size.x += Padding.x*2;
	ret->xPadding = (int)Padding.x;
	ret->yPadding = (int)Padding.y;
	ret->Size.y = (float)TextManager::GetInstance()->GetFontHeight(Font)+(Padding.y*2);
	ret->String = defString;
	ret->Flags = flags;
	ret->font = Font;
	ret->MaxLength = maxLength;
	ret->texture = TextureMgr->getTexture(Graphics);
	ret->xScale = ret->Size.x / ret->texture->getWidth();
	ret->yScale = ret->Size.y / ret->texture->getHeight();
	ret->Enabled = enabled;
	return ret;
}
EditBox* EditBox::CreateEditBox(Pos2D pos, Pos2D size, std::string Font, std::string defString, Texture *Graphics, Pos2D Padding, int flags, int maxLength, bool enabled)
{
	EditBox* ret = new EditBox;
	ret->Position = pos;
	ret->Size = size;
	ret->Size.x += Padding.x*2;
	ret->xPadding = (int)Padding.x;
	ret->yPadding = (int)Padding.y;
	ret->Size.y = (float)TextManager::GetInstance()->GetFontHeight(Font)+(Padding.y*2);
	ret->String = defString;
	ret->Flags = flags;
	ret->font = Font;
	ret->MaxLength = maxLength;
	ret->texture = Graphics;
	ret->xScale = ret->Size.x / ret->texture->getWidth();
	ret->yScale = ret->Size.y / ret->texture->getHeight();
	ret->Enabled = enabled;
	return ret;
}

void EditBox::Update(Uint32 TickDelta)
{
	if(Enabled)
	{
		if(Input->MouseDown(MOUSE_LEFT))
		{
			Pos2D mousePos = Input->GetMousePosition();
			mousePos.x -= Position.x-Size.x/2;
			mousePos.y -= Position.y-Size.y/2;
			if(mousePos.x >= 0 && mousePos.x < Size.x && mousePos.y >= 0 && mousePos.y < Size.y)
			{
				Focus = true;
				Flash = true;
				FlashTimer = 0;
				RepeatTimer = 0;
			}
			else
				Focus = false;
		}

		bool PutChar = false;
		bool Erase = false;
		bool Delete = false;
		char c = 0;
		// Warning: Massive flipping if-sequence!
		if(Focus)
		{
			if(Flags & CEDIT_ALLOW_NUMBERS)
			{
				if(Input->KeyDown(SDLK_0) || (Input->KeyHeld(SDLK_0) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? ')' : '0';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_1) || (Input->KeyHeld(SDLK_1) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '!' : '1';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_2) || (Input->KeyHeld(SDLK_2) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '@"' : '2';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_3) || (Input->KeyHeld(SDLK_3) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '#' : '3';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_4) || (Input->KeyHeld(SDLK_4) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '$' : '4';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_5) || (Input->KeyHeld(SDLK_5) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '%' : '5';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_6)|| (Input->KeyHeld(SDLK_6) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '^' : '6';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_7)|| (Input->KeyHeld(SDLK_7) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '&' : '7';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_8) || (Input->KeyHeld(SDLK_8) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '*' : '8';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_9) || (Input->KeyHeld(SDLK_KP9) && RepeatTimer >= RepeatThreshhold))
				{
					c = (Input->ShiftHeld() && (Flags & CEDIT_ALLOW_SPECIAL)) ? '(' : '9';
					PutChar = true;
					RepeatTimer = 0;
				}
			}
			if(Flags & CEDIT_ALLOW_SPECIAL)
			{
				if(Input->KeyDown(SDLK_COMMA) || (Input->KeyHeld(SDLK_COMMA) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'<':',';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_PERIOD) || (Input->KeyHeld(SDLK_PERIOD) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'>':'.';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_QUOTE) || (Input->KeyHeld(SDLK_QUOTE) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'\"':'\'';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_MINUS) || (Input->KeyHeld(SDLK_MINUS) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'_':'-';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_SLASH) || (Input->KeyHeld(SDLK_SLASH) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'?':'/';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_SEMICOLON) || (Input->KeyHeld(SDLK_SEMICOLON) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?':':';';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_LEFTBRACKET) || (Input->KeyHeld(SDLK_LEFTBRACKET) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'{':'[';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_RIGHTBRACKET) || (Input->KeyHeld(SDLK_RIGHTBRACKET) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'}':']';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_EQUALS) || (Input->KeyHeld(SDLK_EQUALS) && RepeatTimer >= 200))
				{
					c = (Input->ShiftHeld())?'+':'=';
					PutChar = true;
					RepeatTimer = 0;
				}
			}
			if(Flags & CEDIT_ALLOW_KEYPADNUMBERS)
			{
				if(Input->KeyDown(SDLK_KP0) || (Input->KeyHeld(SDLK_KP0) && RepeatTimer >= RepeatThreshhold))
				{
					c = '0';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP1)|| (Input->KeyHeld(SDLK_KP1) && RepeatTimer >= RepeatThreshhold))
				{
					c = '1';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP2) || (Input->KeyHeld(SDLK_KP2) && RepeatTimer >= RepeatThreshhold))
				{
					c = '2';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP3) || (Input->KeyHeld(SDLK_KP3) && RepeatTimer >= RepeatThreshhold))
				{
					c = '3';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP4) || (Input->KeyHeld(SDLK_KP4) && RepeatTimer >= RepeatThreshhold))
				{
					c = '4';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP5) || (Input->KeyHeld(SDLK_KP5) && RepeatTimer >= RepeatThreshhold))
				{
					c = '5';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP6) || (Input->KeyHeld(SDLK_KP6) && RepeatTimer >= RepeatThreshhold))
				{
					c = '6';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP7) || (Input->KeyHeld(SDLK_KP7) && RepeatTimer >= RepeatThreshhold))
				{
					c = '7';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP8) || (Input->KeyHeld(SDLK_KP8) && RepeatTimer >= RepeatThreshhold))
				{
					c = '8';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP9) || (Input->KeyHeld(SDLK_KP9) && RepeatTimer >= RepeatThreshhold))
				{
					c = '9';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_KP_PERIOD) || (Input->KeyHeld(SDLK_KP_PERIOD) && RepeatTimer >= 200))
				{
					c = '.';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Flags & CEDIT_ALLOW_SPECIAL)
				{
					if(Input->KeyDown(SDLK_KP_DIVIDE) || (Input->KeyHeld(SDLK_KP_DIVIDE) && RepeatTimer >= 200))
					{
						c = '/';
						PutChar = true;
						RepeatTimer = 0;
					}
					if(Input->KeyDown(SDLK_KP_EQUALS) || (Input->KeyHeld(SDLK_KP_EQUALS) && RepeatTimer >= 200))
					{
						c = '=';
						PutChar = true;
						RepeatTimer = 0;
					}
					if(Input->KeyDown(SDLK_KP_MINUS) || (Input->KeyHeld(SDLK_KP_MINUS) && RepeatTimer >= 200))
					{
						c = '-';
						PutChar = true;
						RepeatTimer = 0;
					}
					if(Input->KeyDown(SDLK_KP_MULTIPLY) || (Input->KeyHeld(SDLK_KP_MULTIPLY) && RepeatTimer >= 200))
					{
						c = '*';
						PutChar = true;
						RepeatTimer = 0;
					}
					if(Input->KeyDown(SDLK_KP_PLUS) || (Input->KeyHeld(SDLK_KP_PLUS) && RepeatTimer >= 200))
					{
						c = '+';
						PutChar = true;
					}
				}
			}
			if(Flags & CEDIT_ALLOW_TEXT)
			{
				if(Input->KeyDown(SDLK_a) || (Input->KeyHeld(SDLK_a) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'A' : 'a';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_b) || (Input->KeyHeld(SDLK_b) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'B' : 'b';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_c) || (Input->KeyHeld(SDLK_c) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'C' : 'c';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_d) || (Input->KeyHeld(SDLK_d) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'D' : 'd';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_e) || (Input->KeyHeld(SDLK_e) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'E' : 'e';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_f) || (Input->KeyHeld(SDLK_f) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'F' : 'f';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_g) || (Input->KeyHeld(SDLK_g) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'G' : 'g';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_h) || (Input->KeyHeld(SDLK_h) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'H' : 'h';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_i) || (Input->KeyHeld(SDLK_i) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'I' : 'i';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_j) || (Input->KeyHeld(SDLK_j) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'J' : 'j';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_k) || (Input->KeyHeld(SDLK_k) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'K' : 'k';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_l) || (Input->KeyHeld(SDLK_l) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'L' : 'l';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_m) || (Input->KeyHeld(SDLK_m) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'M' : 'm';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_n) || (Input->KeyHeld(SDLK_n) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'N' : 'n';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_o) || (Input->KeyHeld(SDLK_o) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'O' : 'o';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_p) || (Input->KeyHeld(SDLK_p) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'P' : 'p';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_q) || (Input->KeyHeld(SDLK_q) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'Q' : 'q';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_r) || (Input->KeyHeld(SDLK_r) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'R' : 'r';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_s) || (Input->KeyHeld(SDLK_s) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'S' : 's';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_t) || (Input->KeyHeld(SDLK_t) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'T' : 't';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_u) || (Input->KeyHeld(SDLK_u) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'U' : 'u';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_v) || (Input->KeyHeld(SDLK_v) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'V' : 'v';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_w) || (Input->KeyHeld(SDLK_w) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'W' : 'w';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_x) || (Input->KeyHeld(SDLK_x) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'X' : 'x';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_y) || (Input->KeyHeld(SDLK_y) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'Y' : 'y';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_z) || (Input->KeyHeld(SDLK_z) && RepeatTimer >= RepeatThreshhold))
				{
					c = ((Input->ShiftHeld() && !Input->CapsLock()) || (!Input->ShiftHeld() && Input->CapsLock())) ? 'Z' : 'z';
					PutChar = true;
					RepeatTimer = 0;
				}
				if(Input->KeyDown(SDLK_SPACE) || (Input->KeyHeld(SDLK_SPACE) && RepeatTimer >= RepeatThreshhold))
				{
					c = ' ';
					PutChar = true;
					RepeatTimer = 0;
				}
			}
			
			if(Input->KeyDown(SDLK_BACKSPACE) || (Input->KeyHeld(SDLK_BACKSPACE) && RepeatTimer >= RepeatThreshhold))
			{
				Erase = true;
				RepeatTimer = 0;
			}
			else if(Input->KeyDown(SDLK_DELETE) || (Input->KeyHeld(SDLK_DELETE) && RepeatTimer >= RepeatThreshhold))
			{
				Delete = true;
				RepeatTimer = 0;
			}
			else if(Input->KeyDown(SDLK_LEFT) || (Input->KeyHeld(SDLK_LEFT) && RepeatTimer >= RepeatThreshhold))
			{
				StrPos--;
				if(StrPos == (size_t)-1)
					StrPos = 0;
				RepeatTimer = 0;
			}
			else if(Input->KeyDown(SDLK_RIGHT) || (Input->KeyHeld(SDLK_RIGHT) && RepeatTimer >= RepeatThreshhold))
			{
				StrPos++;
				if(StrPos > String.length())
					StrPos = String.length();
				RepeatTimer = 0;
			}

			if(PutChar && ((int)String.length() < MaxLength || MaxLength == 0))
			{
				if(StrPos == String.length())
				{
					String.append(" ");
					String[StrPos] = c;
					StrPos++;
				}
				else
				{
					String.insert(StrPos," ");
					String[StrPos] = c;
					StrPos++;
				}
			}
			else if(Input->KeyDown(SDLK_END))
			{
				StrPos = String.length();
			}
			else if(Input->KeyDown(SDLK_HOME))
			{
				StrPos = 0;
			}
			else if(Erase)
			{
				if(String.length() > 0)
				{
					String.erase(StrPos-1, 1);
					StrPos--;
					Erase = false;
				}
			}
			else if(Delete)
			{
				if(String.length() > 0 && StrPos != String.length())
				{
					String.erase(StrPos, 1);
					Delete = false;
				}
			}
			FlashTimer += TickDelta;
			RepeatTimer += TickDelta;
		}
	}
}

std::string EditBox::GetString()
{
	return String;
}

void EditBox::Draw()
{
	if(Enabled)
		texture->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, xScale, yScale, true, 0.0f);
	else
		texture->Draw(Position.x, Position.y, 0.5f, 0.5f, 0.5f, 1.0f, xScale, yScale, true, 0.0f);
	std::string StringCpy = String;
	if(FlashTimer >= 300 && Enabled)
	{
		Flash = !Flash;
		FlashTimer = 0;
	}
	if(Focus && Flash && Enabled)
		StringCpy.insert(StrPos, "\x7C");
	else if(Focus)
		StringCpy.insert(StrPos, " ");
	if(StringCpy != "")
	{
		int n = 0;
		int z = StringCpy.length();
		int StringWidth = TextManager::GetInstance()->GetStringWidth(font,StringCpy.substr(n, z+1));
		if(StringWidth >= Size.x-xPadding)
		{
			n = StrPos-StrPos/2;
			int NextStringWidth = TextManager::GetInstance()->GetStringWidth(font,StringCpy.substr(n, z+1));
			while(NextStringWidth >= Size.x-xPadding)
			{
				z--;
				NextStringWidth = TextManager::GetInstance()->GetStringWidth(font,StringCpy.substr(n, z+1));
			}
			
		}	
		
		StringCpy = StringCpy.substr(n, z+1);
		StaticText* txt = TextManager::GetInstance()->GetStaticString(font, StringCpy, Pos2D(0,0), Tint(1.0f, 1.0f, 1.0f, 1.0f));
		txt->GetTexture()->Draw((Position.x-(Size.x/2))+xPadding, Position.y-Size.y/2+yPadding, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, false, 0.0f);
		txt->Destroy();
	}
}

void EditBox::Destroy()
{
	texture->Release();
}

void EditBox::GiveFocus(bool focus)
{
	Focus = focus;
}

bool EditBox::HasFocus()
{
	return Focus;
}

void EditBox::Enable()
{
	Enabled = true;
}

void EditBox::Disable()
{
	Enabled = false;
}

bool EditBox::IsEnabled()
{
	return Enabled;
}