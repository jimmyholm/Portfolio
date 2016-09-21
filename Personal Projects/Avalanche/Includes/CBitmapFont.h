#ifndef SFMLG_CBITMAPFONT_H
#define SFMLG_CBITMAPFONT_H
#include <SFML\Graphics.hpp>
#include <SFML\System.hpp>
#include "CSTextureManager.h"
#include "CBitmapText.h"
#include <boost\smart_ptr.hpp>
#include <hash_map>

typedef boost::shared_ptr<CBitmapText> BMPTEXTPTR;
class CBitmapFont
{
	protected:
		bool													m_Loaded;
		TEXPTR													m_FontTexture;
		unsigned short											m_Kerning;
		stdext::hash_map<char, unsigned short>					m_SpecialKerning;
		unsigned short											m_LineHeight;
		unsigned short											m_LineSpacing;
		stdext::hash_map<char, sf::IntRect>						m_CharacterMap;
		sf::Color												m_Emphasis[9];
				
	public:
		CBitmapFont();
		bool		LoadFontFile(std::string Filename);
		sf::IntRect GetStringBoundaries(sf::String Text);
		BMPTEXTPTR  CreateText(sf::String Text, sf::Color Color);
		void		SetEmphasis(size_t index, sf::Color Color);
};

#endif