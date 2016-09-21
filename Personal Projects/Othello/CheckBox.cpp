#include "CheckBox.h"

CheckBox::CheckBox(void) : Label(""), Checked(false), Position(Pos2D(0,0))
{
}

CheckBox::~CheckBox(void)
{
}

CheckBox* CheckBox::CreateCheckbox(Pos2D position, std::string Font, std::string label, bool checked, bool enabled)
{
	CheckBox* ret = new CheckBox;
	ret->Label = label;
	ret->Checked = checked;
	ret->Enabled = enabled;
	ret->Position = position;
	ret->Input = InputHandler::GetInstance();
	SDL_Surface* srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 16, 16,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, 15, 15, 0, 0, 0, 255);
	boxRGBA(srf, 1, 1, 14, 14, 0XE0, 0xE0, 0xE0, 255);
	ret->Check[0] = new Texture;
	ret->Check[0]->TextureFromSurface(srf);
	srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 16, 16,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, 15, 15, 0, 0, 0, 255);
	boxRGBA(srf, 1, 1, 14, 14, 0xE0, 0xE0, 0xE0, 255);
	boxRGBA(srf, 3, 3, 12, 12, 0x00, 0x00, 0x00, 255);
	ret->Check[1] = new Texture;
	ret->Check[1]->TextureFromSurface(srf);
	srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 16, 16,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, 15, 15, 0, 0, 0, 255);
	boxRGBA(srf, 1, 1, 14, 14, 0x90, 0x90, 0x90, 255);
	ret->Check[2] = new Texture;
	ret->Check[2]->TextureFromSurface(srf);
	srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, 16, 16,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	boxRGBA(srf, 0, 0, 15, 15, 0, 0, 0, 255);
	boxRGBA(srf, 1, 1, 14, 14, 0x90, 0x90, 0x90, 255);
	boxRGBA(srf, 3, 3, 12, 12, 0x40, 0x40, 0x40, 255);
	ret->Check[3] = new Texture;
	ret->Check[3]->TextureFromSurface(srf);

	ret->Text = TextManager::GetInstance()->GetStaticString(Font, ret->Label, Pos2D(0,0), Tint(255, 255, 255, 255));
	return ret;
}

void CheckBox::Update()
{
	if(Input->MouseDown(MOUSE_LEFT) && Enabled)
	{
		Pos2D mousePos = Input->GetMousePosition();
		Pos2D size = Pos2D(16,16);//Pos2D(Surface->GetWidth(), Surface->GetHeight());
		mousePos.x -= Position.x-8;
		mousePos.y -= Position.y-8;
		if(mousePos.x >= 0 && mousePos.x < size.x && mousePos.y >= 0 && mousePos.y < size.y)
		{
			Checked = !Checked;
		}
	}
}

void CheckBox::Draw()
{
	float tx = Position.x + 10 + (Text->GetTexture()->getWidth()/2);
	if(Enabled)
	{
		if(Checked)
		{
			Check[1]->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
			TextureMgr->DrawTexture(Check[1]);	
		}
		else
		{
			Check[0]->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
			TextureMgr->DrawTexture(Check[0]);	
		}
	}
	else
	{
		if(Checked)
		{
			Check[3]->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
			TextureMgr->DrawTexture(Check[1]);	
		}
		else
		{
			Check[2]->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
			TextureMgr->DrawTexture(Check[0]);	
		}
	}

	Text->GetTexture()->Draw(tx, Position.y+(Check[0]->getHeight()-Text->GetTexture()->getHeight()), 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, true, 0.0f);
	TextureMgr->DrawTexture(Text->GetTexture());
}

void CheckBox::Destroy()
{
	Text->Destroy();
	Check[0]->Release();
	Check[1]->Release();
}

bool CheckBox::IsChecked()
{
	return Checked;
}

void CheckBox::Enable()
{
	Enabled = true;
}

void CheckBox::Disable()
{
	Enabled = false;
}

bool CheckBox::IsEnabled()
{
	return Enabled;
}