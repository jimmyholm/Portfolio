#pragma once
#include "Texture.h"
#include "utility.h"

class DrawableText
{
	protected:
		Texture* m_Texture;
		Pos2D	 m_Position;
		Tint	 m_Tint;
		bool	 m_IsDead;
	public:
		Texture* GetTexture() { return m_Texture; }
		bool	 IsDead()	  { return m_IsDead;  }
		virtual void Update(Uint32 TickDelta)	= 0;
		virtual void Draw()		= 0;
		virtual void Draw(Pos2D Position, Tint tint, Pos2D scale, float rotation){}
		virtual void Destroy()	= 0;
};