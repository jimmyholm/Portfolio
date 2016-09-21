#pragma once
#include "DrawableText.h"

class StaticText : public DrawableText
{
	protected:

	public:
		
		void Setup(Texture* texture, Pos2D position, Tint tint);
		void Update(Uint32 TickDelta);
		void Draw();
		void Draw(Pos2D Position, Tint tint, Pos2D scale, float rotation);
		void Destroy();
};