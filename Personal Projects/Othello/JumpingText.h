#pragma once
#include "DrawableText.h"
#include "utility.h"

class JumpingText : public DrawableText
{
	protected:
		long	m_TotalTime;
		long	m_LifeTime;
		Pos2D	m_Velocity;
	public:
		void Setup(Texture* texture, Pos2D position, Tint tint, long LifeTime, Pos2D Velocity);
		void Update(Uint32 TickDelta);
		void Draw();
		void Destroy();
};