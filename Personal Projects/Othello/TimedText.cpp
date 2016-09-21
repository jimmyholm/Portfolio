#include "TimedText.h"

void TimedText::Setup(Texture *texture, Pos2D position, Tint tint, long LifeTime)
{
	if(texture == NULL)
		return;
	m_Position	= position;
	m_Texture	= texture;
	m_Texture->addRef();
	m_Tint		= tint;
	m_TimeLeft	= LifeTime;
	m_IsDead = false;
}

void TimedText::Update(Uint32 TickDelta)
{
	m_TimeLeft -= (long)TickDelta;
	if(m_TimeLeft <= 0)
		m_IsDead = true;
}

void TimedText::Draw()
{
	if(m_Texture != NULL)
		m_Texture->Draw(m_Position.x, m_Position.y, m_Tint.R, m_Tint.G, m_Tint.B, m_Tint.A, 1.0f, 1.0f, true, 0.0f); 
}

void TimedText::Destroy()
{
	if(m_Texture != NULL)
	{
		m_Texture->Release();
		if(!m_Texture->isTexture())
			delete m_Texture;
	}
}