#ifndef SFMLG_CBITMAPTEXT_H
#define SFMLG_CBITMAPTEXT_H

#include "CSTextureManager.h"
#include <SFML\Graphics.hpp>

enum eBMPTextAlignment
{
	ALIGN_LEFT = 0,
	ALIGN_CENTER,
	ALIGN_RIGHT
};

class CBitmapText : public sf::Drawable, public sf::Transformable
{
	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
		TEXPTR			m_Texture;
		sf::VertexArray m_Vertices;
	public:	
		void Create(sf::VertexArray VertexArray, sf::Vector2f Origin, TEXPTR Texture);
};

#endif