#pragma once
#include <sdl_opengl.h>
#include "Texture.h"
#include "vertex.h"
#include <map>
#include <string>
#include <fstream>

using std::map;
using std::list;
class TextureManager
{
	private:
		TextureManager();
		static TextureManager*			m_instance;

		map<std::string, Texture*>		m_textures;
		std::list<Texture*>				m_DrawQueue; // The texture draw queue, drawn "back to front"
		bool m_useVBO;
		map<std::string, std::list<std::string> > m_LoadScripts;
	public:
		void AddToDrawQueue(Texture* texture);
		static TextureManager* GetInstance();
		bool LoadTexture(std::string name, std::string file);
		bool ReleaseTexture(std::string name);
		Texture* getTexture(std::string name);
		void ReleaseAll();
		void DrawAll();
		void DrawTexture(Texture* texture);
		void UnloadTexture(std::string TextureName);
		void UseVBO(bool useVBO);
		void LoadScript(std::string name, std::string file);
		void UnloadScript(std::string name);
		void Destroy();
};

#define TextureMgr TextureManager::GetInstance()