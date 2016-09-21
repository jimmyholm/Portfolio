#include "RotoZoomText.h"

void RotoZoomText::Setup(Texture *texture, Pos2D position, Tint tint, long LifeTime, float ScaleFrom, float ScaleTo, float AngleFrom, float AngleTo)
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
	m_ScaleFrom = ScaleFrom;
	m_ScaleTo	= ScaleTo;
	m_AngleFrom = AngleFrom;
	m_AngleTo	= AngleTo;
	m_IsDead = false;
}

void RotoZoomText::Update(Uint32 TickDelta)
{
	m_TotalTime += TickDelta;
	if(m_TotalTime == m_LifeTime)
		m_IsDead = true;
	else
	{
		m_Percent = (float)m_TotalTime/(float)m_LifeTime;
	}
}

void RotoZoomText::Draw()
{

	float Scale = m_ScaleFrom+((m_ScaleTo-m_ScaleFrom)*m_Percent);
	float Angle = m_AngleFrom+((m_AngleTo-m_AngleFrom)*m_Percent);
	float Alpha = m_Tint.A * (1.0f-m_Percent);
	if(m_Texture != NULL)
		m_Texture->Draw(m_Position.x, m_Position.y, m_Tint.R, m_Tint.G, m_Tint.B, Alpha, Scale, Scale, true, Angle); 
}

void RotoZoomText::Destroy()
{
	if(m_Texture != NULL)
	{
		m_Texture->Release();
		if(!m_Texture->isTexture())
			delete m_Texture;
	}
}