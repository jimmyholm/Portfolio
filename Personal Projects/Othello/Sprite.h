#pragma once
#include "AnimationManager.h"

class Sprite
{
	private:
		SpriteAnimation* sprite;
		Pos2D Position;
		std::string CurrentAnimationName;
		Pos2D CurrentAnimation;
		int FramesPerSecond;
		int	CurrentFrame;
		int FrameTime;
		bool isAnimating;
		Tint tint;
		Pos2D scale;
		float rotation;

	public:
		Sprite();
		void Update(Uint32 TickDelta);
		void Draw();
		void MakeSprite(std::string SpriteName, std::string DefaultAnim);
		bool IsAnimating();
		void SetPosition(Pos2D pos);
		Pos2D GetPosition();
		void SetScale(Pos2D Scale);
		Pos2D GetScale();
		void SetTint(Tint color);
		Tint GetTint();
		void SetRotation(float Rotation);
		float GetRotation();
		void SetAnimation(std::string animationName);
		std::string GetAnimationName();
		void Destroy();
};