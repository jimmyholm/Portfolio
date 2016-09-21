#include "Button.h"

Button::Button() : ReturnValue(0)
{
	Position.x = 0;
	Position.y = 0;
	HalfSize.x = 0;
	HalfSize.y = 0;
	TextToDraw = 0;
}

Button::Button(Pos2D position, std::string Font, std::string label, int Returnvalue)
{
	CreateButton(position, Pos2D(0,0), Font, label, Returnvalue);
}

Button* Button::CreateButton(Pos2D position, Pos2D size, std::string Font, std::string label, int Returnvalue)
{
	Button* ReturnBtn = new Button();
	ReturnBtn->ReturnValue = Returnvalue;
	ReturnBtn->Position = position;
	ReturnBtn->Text = TextManager::GetInstance()->GetStaticString(Font, label, Pos2D(0,0), Tint(1.0f,1.0f,1.0f,1.0f));
	if(ReturnBtn->Text->GetTexture()->getWidth()+10 > size.x)
		size.x = ReturnBtn->Text->GetTexture()->getWidth() + 10;
	if(ReturnBtn->Text->GetTexture()->getHeight()+15 > size.y)
		size.y = ReturnBtn->Text->GetTexture()->getHeight()+15;
	// Create the button-textures
	SDL_Surface* srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, (int)size.x, (int)size.y,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

	boxRGBA(srf, 0, 0, srf->w,   srf->h,   0x00, 0x00, 0x00, 0xFF);
	boxRGBA(srf, 1, 1, srf->w-2, srf->h-2, 0xCD, 0xCD, 0xCD, 0xFF);
	boxRGBA(srf, 4, 4, srf->w-5, srf->h-5, 0xDD, 0xDD, 0xDD, 0xFF);//0xCDCDCDFF);
	ReturnBtn->BtnUp = new Texture;
	ReturnBtn->BtnUp->TextureFromSurface(srf);
	srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, (int)size.x, (int)size.y,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, srf->w,   srf->h,   0x00, 0x00, 0x00, 0xFF);
	boxRGBA(srf, 1, 1, srf->w-2, srf->h-2, 0xCD, 0xCD, 0xCD, 0xFF);
	boxRGBA(srf, 4, 4, srf->w-5, srf->h-5, 0xED, 0xED, 0xED, 0xFF);
	ReturnBtn->BtnOver = new Texture;
	ReturnBtn->BtnOver->TextureFromSurface(srf);
	srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, (int)size.x, (int)size.y,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, srf->w,   srf->h,   0x00, 0x00, 0x00, 0xFF);
	boxRGBA(srf, 1, 1, srf->w-2, srf->h-2, 0xDD, 0xDD, 0xDD, 0xFF);
	boxRGBA(srf, 4, 4, srf->w-5, srf->h-5, 0xCD, 0xCD, 0xCD, 0xFF);
	ReturnBtn->BtnDown = new Texture;
	ReturnBtn->BtnDown->TextureFromSurface(srf);
	ReturnBtn->HalfSize.x = (float)ReturnBtn->BtnDown->getWidth()  / 2;
	ReturnBtn->HalfSize.y = (float)ReturnBtn->BtnDown->getHeight() / 2;
	ReturnBtn->TextColor = Tint(0.0f, 0.0f, 0.0f, 1.0f);
	ReturnBtn->xScale = ReturnBtn->yScale = 1.0f;
	return ReturnBtn;
}

Button* Button::CreateButton(Pos2D position, Pos2D size, std::string Font, std::string label, int Returnvalue, std::string ButtonUp, std::string ButtonOver,
						  std::string ButtonDown, Tint textColor)
{
	Button* ReturnBtn = new Button();
	ReturnBtn->ReturnValue = Returnvalue;
	ReturnBtn->Position = position;
	ReturnBtn->Text = TextManager::GetInstance()->GetStaticString(Font, label, Pos2D(0,0), Tint(1.0f,1.0f,1.0f,1.0f));
	if(ReturnBtn->Text->GetTexture()->getWidth()+10 > size.x)
		size.x = ReturnBtn->Text->GetTexture()->getWidth() + 10;
	if(ReturnBtn->Text->GetTexture()->getHeight()+15 > size.y)
		size.y = ReturnBtn->Text->GetTexture()->getHeight()+15;
	// Get the textures and decide on the x & y scale.
	ReturnBtn->BtnUp = TextureMgr->getTexture(ButtonUp);
	ReturnBtn->BtnDown = TextureMgr->getTexture(ButtonDown);
	ReturnBtn->BtnOver = TextureMgr->getTexture(ButtonOver);
	ReturnBtn->HalfSize.x = (float)ReturnBtn->BtnDown->getWidth()  / 2;
	ReturnBtn->HalfSize.y = (float)ReturnBtn->BtnDown->getHeight() / 2;
	ReturnBtn->xScale = size.x / ReturnBtn->BtnDown->getWidth();
	ReturnBtn->yScale = size.y / ReturnBtn->BtnDown->getHeight();
	ReturnBtn->TextColor = textColor;
	return ReturnBtn;
}

bool Button::PosOver(Pos2D Pos)
{
	if(Pos.x >= Position.x-HalfSize.x && Pos.x <= Position.x+HalfSize.x && Pos.y >= Position.y-HalfSize.y && Pos.y <= Position.y+HalfSize.y)
		return true;
	return false;
}

void Button::Update()
{
	TextToDraw = 0;
	if(PosOver(InputHandler::GetInstance()->GetMousePosition()))
	{
		TextToDraw = 1;
		if(InputHandler::GetInstance()->MouseHeld(SDL_BUTTON_LEFT))
		{
			TextToDraw = 2;
		}
	}
}

int Button::ButtonPressed()
{
	return ReturnValue;
}

void Button::Draw()
{
	if(TextToDraw == 1)
	{
		BtnOver->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, xScale, yScale, true, 0.0f);
	}
	else if(TextToDraw == 2)
	{
		BtnDown->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, xScale, yScale, true, 0.0f);
	}
	else
	{
		BtnUp->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, xScale, yScale, true, 0.0f);
	}
	Text->GetTexture()->Draw(Position.x, Position.y, TextColor.R, TextColor.G, TextColor.B, TextColor.A, 1.0f, 1.0f, true, 0.0f);
}

void Button::Destroy()
{
	Position.x = HalfSize.x = 0;
	Position.x = HalfSize.y = 0;
	ReturnValue = 0;
	Text->Destroy();
	BtnUp->Release();
	BtnOver->Release();
	BtnDown->Release();
}