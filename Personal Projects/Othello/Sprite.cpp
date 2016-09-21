#include "Sprite.h"

void Sprite::Update(Uint32 TickDelta)
{
	if(sprite == NULL)
		return;
	if(CurrentAnimation.x != -1 && CurrentAnimation.y != -1)
	{
		FrameTime += TickDelta;
		while(FrameTime >= 1000/FramesPerSecond)
		{
			CurrentFrame++;
			if(CurrentFrame > CurrentAnimation.y)
			{
				CurrentFrame = (int)CurrentAnimation.y;
				isAnimating = false;
			}
			FrameTime -= 1000/FramesPerSecond;
		}
	}
}

void Sprite::Draw()
{
	if(sprite == NULL)
		return;
	if(CurrentFrame >= sprite->GetMaxFrame() || CurrentFrame < 0)
		return;
	sprite->GetFrame(CurrentFrame)->Draw(Position.x, Position.y, tint.R, tint.G, tint.B, tint.A, scale.x, scale.y, true, rotation);
}

bool Sprite::IsAnimating()
{
	return isAnimating;
}

Sprite::Sprite()
{
	CurrentFrame = 0;
	tint.R = tint.G = tint.B = tint.A = 1.0f;
	rotation = 0;
	scale = Pos2D(1.0f, 1.0f);
	FrameTime = 0;
	CurrentAnimationName = "";
	CurrentAnimation = Pos2D(-1, -1);
	isAnimating = false;
	Position = Pos2D(0,0);
	FramesPerSecond = 0;
}

void Sprite::MakeSprite(std::string SpriteName, std::string DefaultAnim)
{
	sprite = AnimationManager::GetInstance()->GetAnimation(SpriteName);
	if(sprite != NULL)
	{
		CurrentAnimation = sprite->SetAnimation(DefaultAnim);
		if(CurrentAnimation.x != -1)
		{
			CurrentAnimationName = DefaultAnim;
			CurrentFrame = (int)CurrentAnimation.x;
			FrameTime = 0;
			FramesPerSecond = sprite->GetFrameRate();
		}
	}
}

void Sprite::SetPosition(Pos2D pos)
{
	Position = pos;
}

Pos2D Sprite::GetPosition()
{
	return Position;
}

void Sprite::SetScale(Pos2D Scale)
{
	scale = Scale;
}

Pos2D Sprite::GetScale()
{
	return scale;
}

void Sprite::SetTint(Tint color)
{
	tint = color;
}

Tint Sprite::GetTint()
{
	return tint;
}

void Sprite::SetAnimation(std::string animationName)
{
	if(sprite == 0)
		return;
	CurrentAnimation = sprite->SetAnimation(animationName);
	if(CurrentAnimation.x != -1)
	{
		isAnimating = true;
		CurrentFrame = (int)CurrentAnimation.x;
		CurrentAnimationName = animationName;
		FrameTime = 0;
	}
	else
	{
		isAnimating = false;
		CurrentFrame = -1;
		CurrentAnimationName = "";
		FrameTime = 0;
	}
}

std::string Sprite::GetAnimationName()
{
	return CurrentAnimationName;
}

void Sprite::Destroy()
{
	if(sprite == NULL)
		return;
	sprite->Release();
}