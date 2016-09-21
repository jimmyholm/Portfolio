#include "TextManager.h"

TextManager* TextManager::m_Instance = 0;

TextManager::TextManager() : m_UseVBO(false)
{
	if(TTF_Init() != 0)
		MessageBox(0, "Failed to initialize TextManager", "Critical Error!", MB_ICONERROR|MB_OK);
}

TextManager* TextManager::GetInstance()
{
	if(m_Instance == 0)
		m_Instance = new TextManager;
	return m_Instance;
}

void TextManager::UpdateAll(Uint32 TickDelta)
{
	list<DrawableText*>::iterator it = m_TextToDraw.begin();
	for(; it != m_TextToDraw.end(); it++)
	{
		(*it)->Update(TickDelta);
	}
	hash_map<std::string, StaticTextDraw*>::iterator stit = m_StaticDraw.begin();
	for(; stit != m_StaticDraw.end(); stit++)
	{
		(*stit).second->Alive = false;
	}
}

void TextManager::DrawAll()
{
	list<DrawableText*>::iterator it = m_TextToDraw.begin();
	for(; it != m_TextToDraw.end(); it++)
	{
		(*it)->Draw();
	}
	hash_map<std::string, StaticTextDraw*>::iterator stit = m_StaticDraw.begin();
	for(; stit != m_StaticDraw.end(); stit++)
	{
		StaticTextDraw* statictest = (*stit).second;
		if(!statictest->Positions.empty())
		{
			statictest->Alive = true;
			list<StaticDrawInfo>::iterator sdit = statictest->Positions.begin();
			for(; sdit != statictest->Positions.end(); sdit++)
			{
				StaticDrawInfo sdi = (*sdit);
				statictest->Text->Draw(sdi.position, sdi.tint, sdi.scale, sdi.rotation);
			}
			statictest->Positions.clear();
		}
	}
}

void TextManager::DestroyDead()
{
	list<DrawableText*>::iterator it = m_TextToDraw.begin();
	list<DrawableText*>::iterator destroy = m_TextToDraw.end();
	DrawableText* ttest = NULL;
	for(; it != m_TextToDraw.end();)
	{
		ttest = (*it);
		if(ttest->IsDead())
		{
			destroy = it;
			it++;
			ttest->Destroy();
			delete ttest;
			ttest = NULL;
			m_TextToDraw.erase(destroy);
			destroy = m_TextToDraw.end();
		}
		else
			it++;
	}
	m_TextToDraw.resize(m_TextToDraw.size());
	hash_map<std::string, StaticTextDraw*>::iterator stit = m_StaticDraw.begin();
	hash_map<std::string, StaticTextDraw*>::iterator stitdestroy = m_StaticDraw.end();
	StaticTextDraw* statictest = NULL;
	for(; stit != m_StaticDraw.end();)
	{
		statictest = (*stit).second;
		if(!statictest->Alive)
		{
			stitdestroy = stit;
			stit++;
			statictest->Text->Destroy();
			statictest->Positions.clear();
			delete statictest; statictest = NULL;
			m_StaticDraw.erase(stitdestroy);
			stitdestroy = m_StaticDraw.end();
		}
		else
			stit++;
	}
}

bool TextManager::LoadFont(std::string FontName, std::string FontFile, int ptsize)
{
	if(m_Fonts.find(FontName) == m_Fonts.end())
	{
		TTF_Font* font = TTF_OpenFont(FontFile.c_str(), ptsize);
		if(font == NULL)
			return false;
		m_Fonts[FontName] = font;
		return true;
	}
	return false;
}

void TextManager::UnloadFont(std::string FontName)
{
	if(m_Fonts.find(FontName) != m_Fonts.end())
	{
		TTF_CloseFont(m_Fonts[FontName]);
		m_Fonts.erase(m_Fonts.find(FontName));
	}
}

void TextManager::DrawStaticText(std::string Font, std::string String, Pos2D Position, Tint tint, Pos2D scale, float rotation)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		if(m_StaticDraw.find(String) == m_StaticDraw.end())
		{
			Texture* texture = new Texture();
			SDL_Color c;
			c.r = 255;
			c.g = 255;
			c.b = 255;
			c.unused = 255;
			texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
			if(texture->getWidth() <= 0)
			{
				delete texture;
				return;
			}
			StaticText* text = new StaticText();
			text->Setup(texture, Position, tint);
			StaticTextDraw* drawThis = new StaticTextDraw;
			drawThis->Alive = true;
			drawThis->Text = text;
			StaticDrawInfo sdi;
			sdi.position = Position;
			sdi.tint = tint;
			sdi.scale = scale;
			sdi.rotation = rotation;
			drawThis->Positions.push_back(sdi);
			m_StaticDraw[String] = drawThis;
			TestCntr++;
		}
		else
		{
			StaticDrawInfo sdi;
			sdi.position = Position;
			sdi.tint = tint;
			sdi.scale = scale;
			sdi.rotation = rotation;
			m_StaticDraw[String]->Positions.push_back(sdi);
		}
	}
}

void TextManager::DrawTimedText(std::string Font, std::string String, Pos2D Position, Tint tint, long LifeTime)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		Texture* texture = new Texture();
		SDL_Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.unused = 255;
		texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
		if(texture->getWidth() <= 0)
		{
			delete texture;
			return;
		}
		TimedText* text = new TimedText();
		text->Setup(texture, Position, tint, LifeTime);
		m_TextToDraw.push_back(text);
	}
}

void TextManager::DrawRotoZoomText(std::string Font, std::string String, Pos2D Position, Tint tint, long LifeTime, float ScaleFrom, float ScaleTo, float AngleFrom, float AngleTo)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		Texture* texture = new Texture();
		SDL_Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.unused = 255;
		texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
		if(texture->getWidth() <= 0)
		{
			delete texture;
			return;
		}
		RotoZoomText* text = new RotoZoomText();
		text->Setup(texture, Position, tint, LifeTime, ScaleFrom, ScaleTo, AngleFrom, AngleTo);
		m_TextToDraw.push_back(text);
	}
}
void TextManager::DrawFadingText(std::string Font, std::string String, Pos2D Position, Tint tint, long LifeTime, float AlphaFrom, float AlphaTo)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		Texture* texture = new Texture();
		SDL_Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.unused = 255;
		texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
		if(texture->getWidth() <= 0)
		{
			delete texture;
			return;
		}
		FadingText* text = new FadingText();
		text->Setup(texture, Position, tint, LifeTime, AlphaFrom,AlphaTo);
		m_TextToDraw.push_back(text);
	}
}

void TextManager::DrawJumpingText(std::string Font, std::string String, Pos2D Position, Tint tint, long LifeTime, Pos2D Velocity)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		Texture* texture = new Texture();
		SDL_Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.unused = 255;
		texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
		if(texture->getWidth() <= 0)
		{
			delete texture;
			return;
		}
		JumpingText* text = new JumpingText();
		text->Setup(texture, Position, tint, LifeTime, Velocity);
		m_TextToDraw.push_back(text);
	}
}

StaticText*	TextManager::GetStaticString(std::string Font, std::string String, Pos2D Position, Tint tint)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		Texture* texture = new Texture();
		SDL_Color c;
		c.r = 255;
		c.g = 255;
		c.b = 255;
		c.unused = 255;
		texture->TextureFromSurface(TTF_RenderText_Blended(m_Fonts[Font], String.c_str(), c));
		if(texture->getWidth() <= 0)
		{
			delete texture;
			return NULL;
		}
		StaticText* text = new StaticText();
		text->Setup(texture, Position, tint);
		return text;
	}
	return NULL;
}

void TextManager::ShutDown()
{
	for(map<std::string, TTF_Font*>::iterator fontit = m_Fonts.begin(); fontit != m_Fonts.end(); fontit++)
	{
		TTF_CloseFont(fontit->second);
	}
	for(list<DrawableText*>::iterator textit = m_TextToDraw.begin(); textit != m_TextToDraw.end(); textit++)
	{
		(*textit)->Destroy();
	}
	m_Fonts.clear();
	m_TextToDraw.clear();
	TTF_Quit();
	delete TextManager::m_Instance;
}

int TextManager::GetFontHeight(std::string Font)
{
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		return TTF_FontHeight(m_Fonts[Font]);
	}
	return 0;
}

int TextManager::GetStringWidth(std::string Font, std::string string)
{
	int w = 0;
	if(m_Fonts.find(Font) != m_Fonts.end())
	{
		TTF_SizeText(m_Fonts[Font], string.c_str(), &w, 0);
	}
	return w;
}

void TextManager::LoadScript(std::string scriptname, std::string filename)
{
	if(m_LoadScripts.find(scriptname) != m_LoadScripts.end())
		return;
	std::ifstream f(filename.c_str());
	if(!f.is_open())
	{
		throw std::exception(FormatString("Filename %s couldn't be opened.", filename.c_str()).c_str());
		return;
	}
	char line[1024];
	std::string stline;
	f.getline(line, 1024);
	stline = std::string(line);
	if(stline != "[Fonts]")
	{
		f.close();
		throw std::exception(FormatString("File %s is not a text loadscript.", filename.c_str()).c_str());
		return;
	}
	std::list<std::string> nameList;
	while(!f.eof())
	{
		f.getline(line, 1024);
		stline = std::string(line);
		std::string name2(""), file2(""), ptsize("");
		name2 = stline.substr(0, stline.find(':'));
		file2 = stline.substr(stline.find(':')+1, stline.length()-stline.find(':'));
		ptsize = file2.substr(file2.find(':')+1, file2.length()-stline.find(':'));
		file2 = file2.substr(0,file2.find(':'));

		if(name2 != "" && file2 != "" && ptsize != "")
		{
			nameList.push_back(name2);
			LoadFont(name2, file2, atoi(ptsize.c_str()));
		}
	}
	f.close();
	m_LoadScripts[scriptname] = std::list<std::string>(nameList);
	nameList.clear();
}

void TextManager::UnloadScript(std::string scriptname)
{
	if(m_LoadScripts.find(scriptname) != m_LoadScripts.end())
	{
		for(std::list<std::string>::iterator it = m_LoadScripts[scriptname].begin(); it != m_LoadScripts[scriptname].end(); it++)
		{
			UnloadFont((*it));
		}
		m_LoadScripts[scriptname].clear();
		m_LoadScripts.erase(m_LoadScripts.find(scriptname));
	}
}