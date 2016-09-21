#include "Particle.h"

Particle::Particle( Pos2D position, Pos2D scale, Tint tint, Pos2D velocity, Pos2D velocityDecay, 
					Pos2D gravity, float angle, float angularVelocity, float angularDecay, int lifeTime) :
					m_Position(position), m_Scale(scale), m_Tint(tint), m_Velocity(velocity), 
					m_VelocityDecay(velocityDecay),	m_Gravity(gravity), m_Angle(angle), m_AngularVelocity(angularVelocity),
					m_AngularDecay(angularDecay), m_TimeLeft(lifeTime)
{
	m_OriginalAlpha = tint.A;
	m_LifeTime = m_TimeLeft;
}

void Particle::Update(Uint32 TickDelta)
{
	float percent = (float)TickDelta/1000.0f;
	m_Position.x += (m_Velocity.x + m_Gravity.x)*percent;
	m_Position.y += (m_Velocity.y + m_Gravity.y)*percent;
	if(m_Velocity.x < 0.0f)
	{
		m_Velocity.x += m_VelocityDecay.x*percent;
		if(m_Velocity.x > 0.0f)
			m_Velocity.x = 0.0f;
	}
	else if(m_Velocity.x > 0.0f)
	{
		m_Velocity.x -= m_VelocityDecay.x*percent;
		if(m_Velocity.x < 0.0f)
			m_Velocity.x = 0.0f;
	}
	if(m_Velocity.y < 0.0f)
	{
		m_Velocity.y += m_VelocityDecay.y*percent;
		if(m_Velocity.y > 0.0f)
			m_Velocity.y = 0.0f;
	}
	else if(m_Velocity.y > 0.0f)
	{
		m_Velocity.y -= m_VelocityDecay.y*percent;
		if(m_Velocity.y < 0.0f)
			m_Velocity.y = 0.0f;
	}

	m_Angle += m_AngularVelocity*percent;
	if(m_Angle < 0.0f)
		m_Angle += 360.0f;
	if(m_Angle > 360.0f)
		m_Angle -= 360.0f;
	if(m_AngularVelocity != 0.0f && m_AngularDecay != 0.0f)
	{
		if(m_AngularVelocity > 0.0f)
		{
			m_AngularVelocity -= m_AngularDecay * percent;
			if(m_AngularVelocity < 0.0f)
				m_AngularVelocity = 0.0f;
		}
		else
		{
			m_AngularVelocity += m_AngularDecay * percent;
			if(m_AngularVelocity >  0.0f)
				m_AngularVelocity = 0.0f;
		}
	}
	m_Tint.A = m_OriginalAlpha * (float)((float)m_TimeLeft/(float)m_LifeTime);
	m_TimeLeft -= TickDelta;
}