#define WIN32_LEAN_AND_MEAN
#define NO_SDL_GLEXT
#include <windows.h>
#include <exception>
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	try
	{
		if(GAME->Initialize(1024,768, 32, true, false))
		{
			GAME->StartLoop();
		}
	}
	catch(std::exception e)
	{
		MessageBox(NULL, e.what() , "Error!", MB_ICONERROR|MB_OK);
		return 1;
	}

	return 0;
}