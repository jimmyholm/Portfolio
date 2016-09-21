#include "CBitmapText.h"

void CBitmapText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = m_Texture.get();
	states.transform *= getTransform();
	target.draw(m_Vertices, states);
}

void CBitmapText::Create(sf::VertexArray VertexArray, sf::Vector2f Origin, TEXPTR texture)
{
	m_Vertices = sf::VertexArray(sf::Quads, VertexArray.getVertexCount());
	unsigned int vCount = VertexArray.getVertexCount();
	unsigned int index;
	for(index = 0; index < vCount; index++)
	{
		m_Vertices[index] = VertexArray[index];
	}
	setOrigin(Origin);
	m_Texture = texture;
}