#include "JumpingText.h"

void JumpingText::Setup(Texture *texture, Pos2D position, Tint tint, long LifeTime, Pos2D Velocity)
{
	if(texture == NULL)
		return;
	m_Position	= position;
	m_Texture	= texture;
	m_Texture->addRef();
	m_Tint		= tint;
	m_LifeTime	= LifeTime;
	m_TotalTime = 0;
	m_Velocity = Velocity;
	m_IsDead = false;
}

void JumpingText::Update(Uint32 TickDelta)
{
	m_TotalTime += TickDelta;
	if(m_TotalTime >= m_LifeTime)
		m_IsDead = true;
	m_Position.x += m_Velocity.x * ((float)TickDelta/1000.0f);
	m_Position.y += m_Velocity.y * ((float)TickDelta/1000.0f);
	if(m_Velocity.y < 100.0f)
		m_Velocity.y += abs(m_Velocity.y/30.0f) + 10.0f;
	if(m_Velocity.x > 0.0f)
		m_Velocity.x -= m_Velocity.x/10.0f;
	if(m_Velocity.x < 0.0f)
		m_Velocity.x += m_Velocity.x/10.0f;
}

void JumpingText::Draw()
{

	float Alpha = m_Tint.A * (1.0f-((float)m_TotalTime/(float)m_LifeTime));
	if(m_Texture != NULL)
		m_Texture->Draw(m_Position.x, m_Position.y, m_Tint.R, m_Tint.G, m_Tint.B, Alpha, 1.0f, 1.0f, true, 0.0f); 
}

void JumpingText::Destroy()
{
	if(m_Texture != NULL)
	{
		m_Texture->Release();
		if(!m_Texture->isTexture())
			delete m_Texture;
	}
}