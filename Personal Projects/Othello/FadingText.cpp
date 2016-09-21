#include "FadingText.h"

void FadingText::Setup(Texture *texture, Pos2D position, Tint tint, long LifeTime, float AlphaFrom, float AlphaTo)
{
	if(texture == NULL)
		return;
	m_Position	= position;
	m_Texture	= texture;
	m_Texture->addRef();
	m_Tint		= tint;
	m_LifeTime	= LifeTime;
	m_TotalTime = 0;
	m_Percent	= 0;
	m_AlphaFrom = AlphaFrom;
	m_AlphaTo	= AlphaTo;
	m_IsDead = false;
}

void FadingText::Update(Uint32 TickDelta)
{
	m_TotalTime += TickDelta;
	if(m_TotalTime == m_LifeTime)
		m_IsDead = true;
	else
		m_Percent = (float)m_TotalTime/(float)m_LifeTime;
}

void FadingText::Draw()
{
	float Alpha = m_AlphaFrom + ((m_AlphaTo-m_AlphaFrom)*m_Percent);
	if(m_Texture != NULL)
		m_Texture->Draw(m_Position.x, m_Position.y, m_Tint.R, m_Tint.G, m_Tint.B, Alpha, 1.0f, 1.0f, true, 0.0f); 
}

void FadingText::Destroy()
{
	if(m_Texture != NULL)
	{
		m_Texture->Release();
		if(!m_Texture->isTexture())
			delete m_Texture;
	}
}