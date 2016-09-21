#include "CBitmapFont.h"
#include "Pugixml.hpp"

CBitmapFont::CBitmapFont() : m_FontTexture(NULL), m_Kerning(0), m_LineHeight(0), m_Loaded(false)
{
	for(int i = 0; i < 9; i++)
		m_Emphasis[i] = sf::Color::Black;
}

bool CBitmapFont::LoadFontFile(std::string Filename)
{
	pugi::xml_document doc;
	if(!doc.load_file(Filename.c_str()))
	{
		throw std::exception("Failed to load font file.\0");
		return false;
	}
	pugi::xml_node node = doc.root().first_child();
	if(_strcmpi(node.name(), "font\0") != 0)
	{
		throw std::exception("File loaded is not a font definition file.\0");
		return false;
	}

	for(node = node.first_child(); node; node = node.next_sibling())
	{
		if(_strcmpi(node.name(), "Texture\0") == 0)
		{
			m_FontTexture = CSTextureManager::GetInstance()->GetTexture(std::string(node.attribute("name").value()));
			if(m_FontTexture == NULL)
			{
				throw("Requested font texture not loaded!\0");
				return false;
			}
		}
		else if(_strcmpi(node.name(), "Metrics\0") == 0)
		{
			m_Kerning = node.attribute("kerning").as_int();
			m_LineHeight = node.attribute("lineHeight").as_int();
			m_LineSpacing = node.attribute("lineSpacing").as_int();
		}
		else if(_strcmpi(node.name(), "Entry\0") == 0)
		{
			char c = node.attribute("char").value()[0];
			sf::IntRect r(node.attribute("x").as_int(), node.attribute("y").as_int(), node.attribute("w").as_int(), node.attribute("h").as_int());
			m_CharacterMap[c] = r;
		}
		else if(_strcmpi(node.name(), "Kerning\0") == 0)
		{
			char c = node.attribute("char").value()[0];
			unsigned short k = (unsigned short)(node.attribute("kerning").as_int());
			m_SpecialKerning[c] = k;
		}
	}
	m_Loaded = true;
	return true;
}

sf::IntRect CBitmapFont::GetStringBoundaries(sf::String Text)
{
	if(!m_Loaded)
	{
		throw std::exception("Font not ready!\0");
		return sf::IntRect(0,0,0,0);
	}

	if(Text.isEmpty())
	{
		return sf::IntRect(0,0,0,0);
	}
	
	sf::IntRect boundaries(0,0,0, m_LineHeight);
	size_t strlen = Text.getSize();
	size_t index  = 0;
	sf::IntRect charBoundary;
	char c = 0;
	sf::Int32 greatestWidth = 0;
	for(; index != strlen; index++)
	{
		c = Text[index];
		if(c == '\0')
			break;
		else if(c == '\n')
		{
			if(boundaries.width > greatestWidth)
				greatestWidth = boundaries.width;
			boundaries.width = 0;
			if(boundaries.height == m_LineHeight)
				boundaries.height += m_LineSpacing;
			else
				boundaries.height += m_LineHeight+m_LineSpacing;
			continue;
		}
		else if(c == '\\')
		{
			if(index != strlen+1)
			{
				if(Text[index+1] == '%')
					continue;
			}
		}
		else if(c == '%')
		{
			if(index != strlen+1)
			{
				switch(Text[index+1])
				{
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
						index++;
						continue;
				}
			}
		}
		if(m_CharacterMap.find(c) == m_CharacterMap.end())
			charBoundary = m_CharacterMap[' '];
		else
			charBoundary = m_CharacterMap[c];
		boundaries.width += charBoundary.width;

		if(index > 0 && index < strlen-1)
			if(m_SpecialKerning.find(c) == m_SpecialKerning.end())
				boundaries.width += m_Kerning;
			else
				boundaries.width += m_SpecialKerning.find(c)->second;
	}
	if(greatestWidth > boundaries.width)
		boundaries.width = greatestWidth;
	return boundaries;
}

BMPTEXTPTR CBitmapFont::CreateText(sf::String Text, sf::Color Color)
{

	sf::Color useColor = Color;
	if(!m_Loaded)
	{
		throw std::exception("Font not ready!\0");
		return NULL;
	}

	if(Text.isEmpty())
	{
		return NULL;
	}
	sf::IntRect originbdr = GetStringBoundaries(Text);
	sf::Vector2f origin((float)originbdr.width / 2.0f, (float)originbdr.height / 2.0f);
	sf::VertexArray Vertices(sf::Quads, (Text.getSize())*4);
	sf::Vector2f pos(0,0);
	sf::Vector2f ttl, ttr, tbr, tbl;
	sf::IntRect charBndr;
	unsigned int vindex = 0;
	size_t strlen = Text.getSize();
	char c;
	for(size_t i = 0; i < strlen; i++)
	{
		c = Text[i];
		if(c == '\n')
		{
			pos.x = 0;
			pos.y += m_LineHeight + m_LineSpacing;
			continue;
		}
		else if(c == '\\')
		{
			if(i != strlen+1)
			{
				if(Text[i+1] == '%')
					continue;
			}
		}
		else if(c == '%')
		{
			if(i != strlen+1)
			{
				switch(Text[i+1])
				{
					case '0':
						useColor = Color;
						i++;
						continue;
					case '1':
						useColor = m_Emphasis[0];
						i++;
						continue;
					case '2':
						useColor = m_Emphasis[1];
						i++;
						continue;
					case '3':
						useColor = m_Emphasis[2];
						i++;
						continue;
					case '4':
						useColor = m_Emphasis[3];
						i++;
						continue;
					case '5':
						useColor = m_Emphasis[4];
						i++;
						continue;
					case '6':
						useColor = m_Emphasis[5];
						i++;
						continue;
					case '7':
						useColor = m_Emphasis[6];
						i++;
						continue;
					case '8':
						useColor = m_Emphasis[7];
						i++;
						continue;
					case '9':
						useColor = m_Emphasis[8];
						i++;
						continue;
				}
			}
		}
		charBndr = m_CharacterMap[c];
		ttl = sf::Vector2f((float)charBndr.left, (float)charBndr.top);
		ttr = sf::Vector2f((float)(charBndr.left+charBndr.width), (float)charBndr.top);
		tbr = sf::Vector2f((float)(charBndr.left+charBndr.width), (float)(charBndr.top+charBndr.height));
		tbl = sf::Vector2f((float)charBndr.left, (float)(charBndr.top+charBndr.height));
		Vertices[vindex].position = pos;
		Vertices[vindex].texCoords = ttl;
		Vertices[vindex].color = useColor;
		Vertices[vindex+1].position = sf::Vector2f(pos.x+(float)charBndr.width, pos.y);
		Vertices[vindex+1].texCoords = ttr;
		Vertices[vindex+1].color = useColor;
		Vertices[vindex+2].position = sf::Vector2f(pos.x+(float)charBndr.width, pos.y+(float)charBndr.height);
		Vertices[vindex+2].texCoords = tbr;
		Vertices[vindex+2].color = useColor;
		Vertices[vindex+3].position = sf::Vector2f(pos.x, pos.y+(float)charBndr.height);
		Vertices[vindex+3].texCoords = tbl;
		Vertices[vindex+3].color = useColor;

		vindex += 4;
		if(m_SpecialKerning.find(c) == m_SpecialKerning.end())
			pos.x += charBndr.width + m_Kerning;
		else
			pos.x += charBndr.width + m_SpecialKerning.find(c)->second;
	}
	BMPTEXTPTR ret(new CBitmapText);
	ret.get()->Create(Vertices, origin, m_FontTexture);
	return ret;
}

void CBitmapFont::SetEmphasis(size_t index, sf::Color Color)
{
	if( index < 1 || index > 8)
		return;
	m_Emphasis[index-1] = Color;
}