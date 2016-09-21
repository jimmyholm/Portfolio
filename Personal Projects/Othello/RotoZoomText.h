#pragma once
#include "DrawableText.h"

class RotoZoomText : public DrawableText
{
	protected:
		long	m_TotalTime;
		long	m_LifeTime;
		float	m_ScaleFrom;
		float	m_ScaleTo;
		float	m_AngleFrom;
		float	m_AngleTo;
		float	m_Percent;
	public:
		void Setup(Texture* texture, Pos2D position, Tint tint, long LifeTime, float ScaleFrom, float ScaleTo, float AngleFrom, float AngleTo);
		void Update(Uint32 TickDelta);
		void Draw();
		void Destroy();
};