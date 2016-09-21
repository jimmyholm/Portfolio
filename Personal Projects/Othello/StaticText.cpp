#include "StaticText.h"

void StaticText::Setup(Texture *texture, Pos2D position, Tint tint)
{
	if(texture == NULL)
		return;
	m_Position	= position;
	m_Texture	= texture;
	m_Texture->addRef();
	m_Tint		= tint;
	m_IsDead = false;
}

void StaticText::Update(Uint32 TickDelta)
{
}

void StaticText::Draw()
{
	if(m_Texture != NULL)
		m_Texture->Draw(m_Position.x, m_Position.y, m_Tint.R, m_Tint.G, m_Tint.B, m_Tint.A, 1.0f, 1.0f, true, 0.0f); 
	m_IsDead = true;
}
void StaticText::Draw(Pos2D Position, Tint tint, Pos2D scale, float rotation)
{
	if(m_Texture != NULL)
		m_Texture->Draw(Position.x, Position.y, tint.R, tint.G, tint.B, tint.A, scale.x, scale.y, true, rotation);
	m_IsDead = true;
}

void StaticText::Destroy()
{
	if(m_Texture != NULL)
	{
		m_Texture->Release();
		if(!m_Texture->isTexture())
			delete m_Texture;
	}
}