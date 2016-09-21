#include "SpriteAnimation.h"


void SpriteAnimation::Destroy()
{
	for(size_t i = 0 ; i < Frames.size(); i++)
		Frames[i]->Release();
	Frames.clear();
}

void SpriteAnimation::AddFrame(std::string texturename)
{
	Texture* add = TextureMgr->getTexture(texturename);
	if(add != NULL)
	{
		Frames.push_back(add);
		MaxFrame++;
	}
}

void SpriteAnimation::AddFrame(Texture *texture)
{
	if(texture != NULL)
	{
		texture->addRef();
		Frames.push_back(texture);
		MaxFrame++;
	}
}

void SpriteAnimation::AddAnimation(std::string animationName, Pos2D FrameLimits)
{
	if(AnimationData.find(animationName) != AnimationData.end())
	{
		return;
	}
	AnimationData[animationName] = FrameLimits;
}
Pos2D SpriteAnimation::SetAnimation(std::string animationName)
{
	if(AnimationData.find(animationName) != AnimationData.end())
	{
		return AnimationData[animationName];
	}
	return Pos2D(-1, -1);
}

SpriteAnimation::SpriteAnimation(int FPS)
{
	FramesPerSecond = FPS;
	refcount = 0;
	MaxFrame = 0;
	Alive = true;
}

void SpriteAnimation::AddRef()
{
	refcount++;
}

bool SpriteAnimation::Release()
{
	if(--refcount <= 0)
	{
		Destroy();
		delete this;
		return false;
	}
	return true;
}

bool SpriteAnimation::isAlive()
{
	return Alive;
}

int SpriteAnimation::GetMaxFrame()
{
	return MaxFrame;
}

int SpriteAnimation::GetFrameRate()
{
	return FramesPerSecond;
}

Texture* SpriteAnimation::GetFrame(int frame)
{
	if(frame >= 0 && frame < (int)Frames.size())
		return Frames[frame];
	return NULL;
}