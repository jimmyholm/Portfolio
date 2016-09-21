#pragma once
#include "TextureManager.h"
#include "utility.h"
class TextureFade
{
	protected:
		Texture* texture;
		Tint TintFrom;
		Tint TintTo;
		int LifeTime;
		int TimeLeft;
		Pos2D Position;
		Pos2D ScaleFrom;
		Pos2D ScaleTo;
		float RotationFrom;
		float RotationTo;

	public:
		TextureFade(std::string TextureName, Tint tintFrom, Tint tintTo, int lifeTime, Pos2D position, Pos2D scaleFrom,
					Pos2D scaleTo, float rotationFrom, float rotationTo);
		void Update(Uint32 TickDelta);
		void Draw();
		bool IsAlive();
		void Destroy();
};