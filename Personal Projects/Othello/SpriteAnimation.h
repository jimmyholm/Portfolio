#pragma once
#include "TextureManager.h"
#include "utility.h"

class SpriteAnimation
{
	protected:
		map<std::string, Pos2D> AnimationData;
		std::vector<Texture*> Frames;
		void Destroy();
		int refcount;
		bool Alive;
		int FramesPerSecond;
		int MaxFrame;
	public:
		SpriteAnimation(int FPS);
		Texture* GetFrame(int frame);
		int  GetMaxFrame();
		int	 GetFrameRate();
		void AddFrame(std::string texturename);
		void AddFrame(Texture* texture);
		void AddAnimation(std::string animationName, Pos2D FrameLimits);
		Pos2D SetAnimation(std::string animationName);
		void AddRef();
		bool Release();
		bool isAlive();
};