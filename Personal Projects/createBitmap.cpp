/**
 ** Generate a vertexstrip, textured using a font texture in order to produce 2Dimensional text
 ** on screen.
 ** Written in 2013, part of Avalanche
 **/
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