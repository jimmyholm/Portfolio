#pragma once
#include "DrawableText.h"

class TimedText : public DrawableText
{
	protected:
		long m_TimeLeft;
	public:
		void Setup(Texture* texture, Pos2D position, Tint tint, long LifeTime);
		void Update(Uint32 TickDelta);
		void Draw();
		void Destroy();
};