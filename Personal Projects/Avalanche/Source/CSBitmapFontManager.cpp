#include "CSBitmapFontManager.h"
#include <boost\format.hpp>
CSBitmapFontManager* CSBitmapFontManager::m_Instance = NULL;

CSBitmapFontManager::CSBitmapFontManager() {}

CSBitmapFontManager* CSBitmapFontManager::GetInstance()
{
	if(m_Instance == NULL)
		m_Instance = new CSBitmapFontManager();

	return m_Instance;
}

bool CSBitmapFontManager::LoadFont(std::string FontFile, std::string FontName)
{
	if(m_Fonts.find(FontName) != m_Fonts.end())
	{
		std::string e = boost::str(boost::format("Font \"%1%\" already loaded!") % FontName);
		throw std::exception(e.c_str());
		return false;
	}
	m_Fonts[FontName] = BMPFONTPTR(new CBitmapFont());
	bool ret = m_Fonts[FontName]->LoadFontFile(FontFile);
	if(ret == false)
	{
		std::string e = boost::str(boost::format("Failed to load font from file \"%1%\".") % FontFile);
		throw std::exception(e.c_str());
	}
	return ret;
}

BMPFONTPTR CSBitmapFontManager::GetFont(std::string FontName)
{
	if(m_Fonts.find(FontName) == m_Fonts.end())
	{
		std::string e = boost::str(boost::format("Fontname \"%1%\" not loaded!") % FontName);
		throw std::exception(e.c_str());
		return NULL;
	}

	return m_Fonts[FontName];
}

void CSBitmapFontManager::Clear()
{
	m_Fonts.clear();
	delete CSBitmapFontManager::m_Instance;
	CSBitmapFontManager::m_Instance = NULL;
}