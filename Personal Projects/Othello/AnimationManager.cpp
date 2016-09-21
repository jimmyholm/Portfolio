#include "AnimationManager.h"
#include <exception>

AnimationManager* AnimationManager::Instance = 0;

AnimationManager::AnimationManager()
{
}

AnimationManager* AnimationManager::GetInstance()
{
	if(Instance == NULL)
		Instance = new AnimationManager;
	return Instance;
}

void AnimationManager::AddAnimation(std::string name, SpriteAnimation* animation)
{
	if(Animations.find(name) != Animations.end())
		return;
	Animations[name] = animation;
}

SpriteAnimation* AnimationManager::GetAnimation(std::string name)
{
	if(Animations.find(name) == Animations.end())
		return NULL;
	Animations[name]->AddRef();
	return Animations[name];
}

void AnimationManager::DestroyAnimation(std::string name)
{
	if(Animations.find(name) == Animations.end())
		return;
	while(Animations[name]->Release());
	Animations.erase(Animations.find(name));
}

void AnimationManager::DestroyAll()
{
	for(map<std::string, SpriteAnimation*>::iterator it = Animations.begin(); it != Animations.end();)
	{
		map<std::string, SpriteAnimation*>::iterator destroy = it;
		it++;
		DestroyAnimation(destroy->first);
	}
}

void AnimationManager::DestroyManager()
{
	DestroyAll();
	delete this;
}

void AnimationManager::LoadScript(std::string name, std::string file)
{
	int LoadStep = 0; // 0 = FPS, 1 = Frames, 2 = animations
	std::ifstream f(file.c_str());
	if(!f.is_open())
	{
		throw std::exception(FormatString("Filename %s couldn't be opened.", file.c_str()).c_str());
		return;
	}
	char line[1024];
	std::string stline;
	f.getline(line, 1024);
	stline = std::string(line);
	if(stline != "[Sprite]")
	{
		f.close();
		throw std::exception(FormatString("File %s is not a sprite loadscript.", file.c_str()).c_str());
		return;
	}
	f.getline(line, 1024);
	stline = std::string(line);
	SpriteAnimation* add = new SpriteAnimation(atoi(stline.c_str()));
	while(!f.eof())
	{
		f.getline(line, 1024);
		stline = std::string(line);
		if(stline.empty())
			continue;
		if(LoadStep == 0 && stline != "[Frames]")
		{
			delete add;
			f.close();
			throw std::exception(FormatString("File %s is malformed.", file.c_str()).c_str());
			return;
		}
		else if(LoadStep == 0 && stline == "[Frames]")
		{
			LoadStep = 1;
			continue;
		}
		if(stline == "[Animations]")
		{
			LoadStep = 2;
			continue;
		}
		if(LoadStep == 1)
		{
			if(!stline.empty())
				add->AddFrame(stline);
		}
		if(LoadStep == 2)
		{
			if(!stline.empty())
			{
				std::string name2(""), aData("");
				name2 = stline.substr(0, stline.find('='));
				aData = stline.substr(stline.find('=')+1, stline.length()-stline.find('='));
				Pos2D AnimData;
				AnimData.x = (float)atoi(aData.substr(0, aData.find(',')).c_str());
				AnimData.y = (float)atoi(aData.substr(aData.find(',')+1, aData.length()-aData.find(',')).c_str());
				add->AddAnimation(name2, AnimData);
			}
		}
	}
	AddAnimation(name, add);
	f.close();
}