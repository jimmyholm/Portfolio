#include "DrawableList.h"

DrawableList::DrawableList(void) : Position(Pos2D(0,0)), NumEntries(0), First(0), LinesToDraw(0), Selected(-1)
{
}

DrawableList::~DrawableList(void)
{
}

void DrawableList::init(std::string font, bool drawDividers, Pos2D pos, Pos2D size)
{
	Font = font;
	DrawDividers = drawDividers;
	Position = pos;
	Size = size;
	LineHeight = TextManager::GetInstance()->GetFontHeight(Font)+4;
	LinesToDraw = (size_t)((Size.y-6)/(LineHeight));
	
	//(size_t)( ((float)(Size.y - 2.0f)/2.0f) - (Size.y - 2)/2 > 0) ? ((Size.y - 2)/2)+1 : (Size.y - 2)/2;
	SDL_Surface* srf = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_SRCALPHA, (int)Size.x, (int)Size.y,
											32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
	rectangleRGBA(srf, 0, 0, (Sint16)Size.x-1, (Sint16)Size.y-1, 0x00, 0x00, 0x00, 0xff);
	boxRGBA(srf, 1, 1,		 (Sint16)Size.x-2, (Sint16)Size.y-2, 0xCD, 0xCD, 0xCD, 0xFF);
	boxRGBA(srf, 4, 4,		 (Sint16)Size.x-5, (Sint16)Size.y-5, 0xFF, 0xFF, 0xFF, 0xFF);
	rectangleRGBA(srf, 5, 5, (Sint16)Size.x-6, (Sint16)Size.y-6, 0x00, 0x00, 0x00, 0xff);
	MaxWidth = (int)Size.x - 27-4;
	rectangleRGBA(srf, 6+MaxWidth+4, 5, (Sint16)Size.x-6, (Sint16)Size.y-6, 0x00, 0x00, 0x00, 0xff);
	buttons = new ButtonManager;
	buttons->AddButton(new Button(Pos2D((Position.x + (Size.x/2)-13),Position.y-(Size.y/2)+19), Font, "^", BTN_UP)); 
	buttons->AddButton(new Button(Pos2D((Position.x + (Size.x/2)-13),Position.y+(Size.y/2)-19), Font, "v", BTN_DOWN)); 
	if(DrawDividers)
	{
		int ystart	= 6;
		int xstart  = 6;
		int xend	= 6+MaxWidth+4;
		for(size_t i = 1; i <= LinesToDraw; i++)
			lineRGBA(srf, xstart, ystart+i*LineHeight, xend, ystart+i*LineHeight, 0x00, 0x00, 0x00, 0xFF);
	}
	Background = new Texture;
	Background->TextureFromSurface(srf);
}

DrawableList* DrawableList::CreateList(std::string font, bool drawDividers, Pos2D pos, Pos2D size)
{
	DrawableList* ret = new DrawableList;
	ret->init(font, drawDividers, pos, size);
	return ret;
}

int DrawableList::Entries()
{
	return NumEntries;
}

void DrawableList::AddString(std::string str)
{
	while(TextManager::GetInstance()->GetStringWidth(Font, str) > MaxWidth)
	{
		str = str.substr(0, str.length()-1);
	}
	Strings.push_back(str);
	NumEntries++;
}

void DrawableList::InsertString(std::string str, size_t pos)
{
	if(pos >= NumEntries)
		AddString(str);
	else
	{
		Strings.insert(Strings.begin()+pos, str);
		NumEntries++;
	}
}

void DrawableList::RemoveString(size_t index)
{
	if(index >= 0 && index < NumEntries)
	{
		Strings.erase(Strings.begin()+index);
		NumEntries--;
	}
}

std::string DrawableList::GetString(size_t Index)
{
	if(Index < 0 || Index >= NumEntries)
		return "";

	return Strings[Index];
}

int DrawableList::GetSelected()
{
	return Selected;
}

std::string DrawableList::GetSelection()
{
	if(Selected < 0 || Selected >= (int)NumEntries)
		return "";

	return Strings[Selected];
}

void DrawableList::Draw()
{
	Background->Draw(Position.x, Position.y, 1.0f, 1.0f, 1.0f, 1.0, 1.0f, 1.0f, true, 0.0f);
	TextureMgr->DrawTexture(Background);
	buttons->Draw();
	if(NumEntries == 0)
		return;
	int Lines = ((First + LinesToDraw) > NumEntries) ? NumEntries - First : LinesToDraw;
	float x = (Position.x-Size.x/2) + 8.0f;
	float y = (Position.y-Size.y/2) + 6.0f;
	StaticText* text = new StaticText;
	for(int i = 0; i < Lines; i++)
	{
		text = TextManager::GetInstance()->GetStaticString(Font, Strings[First+i],Pos2D(0,0), Tint(1.0f, 1.0f, 1.0f, 1.0f));
		if(Selected != First+i)
			text->GetTexture()->Draw(x, (float)(y+5+((i*LineHeight)-2)), 0.25f, 0.25f, 0.25f, 1.0f, 1.0f, 1.0f, false, 0.0f);
		else
			text->GetTexture()->Draw(x, (float)(y+5+((i*LineHeight)-2)), 0.50f, 0.50f, 0.50f, 1.0f, 1.0f, 1.0f, false, 0.0f);
		TextureMgr->DrawTexture(text->GetTexture());
		text->Destroy();
	}
}

void DrawableList::Update()
{
	InputHandler* Input = InputHandler::GetInstance();

	if(Input->MouseDown(MOUSE_LEFT))
	{
		Pos2D Pos = Input->GetMousePosition();
		Pos.x -= (Position.x-Size.x/2)+6;
		Pos.y -= (Position.y-Size.y/2)+6;
		if(Pos.x >= 0 && Pos.x < MaxWidth && Pos.y >= 0 && Pos.y < Size.y-6)
		{
			int entry = First+(int)(Pos.y/LineHeight);
			if(entry >= (int)NumEntries || entry < 0)
				Selected = -1;
			else
				Selected = entry;
		}
	}
	if(buttons->Update() == BTN_UP)
		PreviousLine();
	else if(buttons->Update() == BTN_DOWN)
		NextLine();
}

void DrawableList::Destroy()
{
	buttons->DestroyManager();
	Background->Release();
}

void DrawableList::NextPage()
{
	First += LinesToDraw;
	if(First > (int)NumEntries)
		First -= LinesToDraw;
}

void DrawableList::PreviousPage()
{
	First -= LinesToDraw;
	if(First < 0)
		First = 0;
}

void DrawableList::NextLine()
{
	if(First+LinesToDraw < NumEntries)
		First++;
}

void DrawableList::PreviousLine()
{
	if(First > 0)
		First--;
}