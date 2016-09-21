#pragma once
#include "utility.h"
class Particle
{
	public:
		Pos2D	m_Position;
		Pos2D	m_Scale;
		Tint	m_Tint;
		float	m_OriginalAlpha;
		Pos2D	m_Velocity;		// In pixels per second
		Pos2D	m_VelocityDecay;// Decay of velocity
		Pos2D	m_Gravity;		// In pixels per second
		int		m_LifeTime;		
		int		m_TimeLeft;		// In milliseconds
		float	m_Angle;		// In degrees
		float	m_AngularVelocity; // Increase/decrease in angle in degrees per second
		float	m_AngularDecay; // Decay of angular velocity
		
		void Update(Uint32 TickDelta);
		Particle(Pos2D position, Pos2D scale, Tint tint, Pos2D velocity, Pos2D velocityDecay,
				 Pos2D gravity, float angle, float angularVelocity, float angularDecay, int lifeTime);
};