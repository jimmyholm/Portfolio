#pragma once
#include <SDL.h>
#include <SDL_Net.h>

class NetworkManager
{
	protected:
		NetworkManager();
		static NetworkManager* Instance;

	public:
		static NetworkManager* GetInstance();

};