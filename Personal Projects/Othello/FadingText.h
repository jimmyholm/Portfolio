#pragma once
#include "DrawableText.h"

class FadingText : public DrawableText
{
	protected:
		long  m_LifeTime;
		long  m_TotalTime;
		float m_AlphaFrom;
		float m_AlphaTo;
		float m_Percent;
	public:
		void Setup(Texture* texture, Pos2D position, Tint tint, long LifeTime, float AlphaFrom, float AlphaTo);
		void Update(Uint32 TickDelta);
		void Draw();
		void Destroy();
};