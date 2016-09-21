#ifdef _WIN32
#ifndef _DEBUG
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif
#endif
#include <iostream>
#include <fstream>
#include "CApplication.h"
CApplication	App;
#ifdef _WIN32
#ifndef _DEBUG
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#else
int main(int argc, char* argv[])
#endif
#else
int main(int argc, char* argv[])
#endif
{
	App.Initialize();
	App.CreateWindow("Game", 736, 768, (sf::Style::Titlebar | sf::Style::Close));
	try
	{
		App.GameLoop();
	}
	catch(std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	App.ShutDown();
	return 0;
}