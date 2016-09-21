#ifndef SFMLG_CSBITMAPFONTMANAGER_H
#define SFMLG_CSBITMAPFONTMANAGER_H
#include "CBitmapFont.h"
#include <boost/smart_ptr.hpp>
#include <string>
#include <hash_map>

typedef boost::shared_ptr<CBitmapFont> BMPFONTPTR;
class CSBitmapFontManager
{
	private:
		stdext::hash_map<std::string, BMPFONTPTR> m_Fonts;
		static CSBitmapFontManager* m_Instance;
		CSBitmapFontManager();
	public:
		static CSBitmapFontManager* GetInstance();
		bool LoadFont(std::string FontFile, std::string FontName);
		BMPFONTPTR GetFont(std::string FontName);
		void Clear();
};
#endif