#include "TextureFade.h"

TextureFade::TextureFade(std::string TextureName, Tint tintFrom, Tint tintTo, int lifeTime, Pos2D position, 
						 Pos2D scaleFrom, Pos2D scaleTo, float rotationFrom, float rotationTo)
{
	texture = TextureMgr->getTexture(TextureName);
	TintFrom = tintFrom;
	TintTo = tintTo;
	LifeTime = TimeLeft = lifeTime;
	Position = position;
	ScaleFrom = scaleFrom;
	ScaleTo = scaleTo;
	RotationFrom = rotationFrom;
	RotationTo = rotationTo;
}

void TextureFade::Update(Uint32 TickDelta)
{
	TimeLeft -= TickDelta;
}

void TextureFade::Draw()
{
	Tint tint		= TintTo;
	Pos2D scale		= ScaleTo;
	float rotation	= RotationTo;
	float percent	= (float)TimeLeft/(float)LifeTime;
	tint.R += (TintFrom.R-TintTo.R)*percent;
	tint.G += (TintFrom.G-TintTo.G)*percent;
	tint.B += (TintFrom.B-TintTo.B)*percent;
	tint.A += (TintFrom.A-TintTo.A)*percent;
	scale.x += (ScaleFrom.x-ScaleTo.x)*percent;
	scale.y += (ScaleFrom.y-ScaleTo.y)*percent;
	rotation += (RotationFrom-RotationTo)*percent;
	texture->Draw(Position.x, Position.y, tint.R, tint.G, tint.B, tint.A, scale.x, scale.y, true, rotation);
}

void TextureFade::Destroy()
{
	texture->Release();
	if(!texture->isTexture())
		delete texture;
	texture = 0;
}

bool TextureFade::IsAlive()
{
	return (texture != NULL && TimeLeft > 0);
}