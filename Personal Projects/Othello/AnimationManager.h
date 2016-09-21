#pragma once

#include "SpriteAnimation.h"
#include <string>
#include <map>
class AnimationManager
{
	private:
		static AnimationManager* Instance;
		AnimationManager();
		map<std::string, SpriteAnimation*> Animations;
	public:
		static AnimationManager* GetInstance();
		void AddAnimation(std::string name, SpriteAnimation* animation);
		SpriteAnimation* GetAnimation(std::string name);
		void DestroyAnimation(std::string name);
		void DestroyAll();
		void DestroyManager();
		void LoadScript(std::string name, std::string file);
};