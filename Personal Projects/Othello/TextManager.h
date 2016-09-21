#pragma once
#include "TextureManager.h"
#include "DrawableText.h"
#include "TextTypes.h"
#include <SDL_TTF.h>
#include "vertex.h"
#include <map>
#include <list>
#include <hash_map>
using std::map;
using std::list;
using stdext::hash_map;

struct StaticDrawInfo
{
	Pos2D position;
	Pos2D scale;
	Tint  tint;
	float rotation;
};

struct StaticTextDraw
{
	StaticText* Text;
	list<StaticDrawInfo> Positions;
	bool		Alive;
};

class TextManager
{
	private:
		map<std::string, TTF_Font*>	m_Fonts;
		list<DrawableText*>			m_TextToDraw;
		hash_map<std::string, StaticTextDraw*> m_StaticDraw;
		hash_map<std::string, std::list<std::string> > m_LoadScripts;
		static TextManager*			m_Instance;
		bool						m_UseVBO;
		TextManager();
	public:
		static TextManager*			GetInstance();
		void						UpdateAll(Uint32 TickDelta);
		void						DrawAll();
		void						DestroyDead();
		bool						LoadFont(std::string FontName, std::string FontFile, int ptsize);
		void						UnloadFont(std::string FontName);
		void						DrawStaticText(std::string Font, std::string String, Pos2D Position, Tint tint, 
													Pos2D scale = Pos2D(1.0f,1.0f), float rotation = 0.0f);
		void						DrawTimedText(std::string Font, std::string String, Pos2D Position, Tint tint, 
												  long LifeTime);
		void						DrawRotoZoomText(std::string Font, std::string String, Pos2D Position, Tint tint,
													 long LifeTime, float ScaleFrom, float ScaleTo, float AngleFrom, 
													 float AngleTo);
		void						DrawFadingText(std::string Font, std::string String, Pos2D Position, Tint tint, 
												  long LifeTime, float AlphaFrom, float AlphaTo);
		void						DrawJumpingText(std::string Font, std::string String, Pos2D Position, Tint tint, 
												  long LifeTime, Pos2D Velocity);
		StaticText*					GetStaticString(std::string Font, std::string String, Pos2D Position, Tint tint);
		int							GetFontHeight(std::string Font);
		int							GetStringWidth(std::string Font, std::string string);
		void						LoadScript(std::string scriptname, std::string filename);
		void						UnloadScript(std::string name);
		void						ShutDown();
};