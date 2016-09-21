#pragma once
#include "utility.h"
#include <sdl.h>
#include <sdl_opengl.h>
#include <sdl_mixer.h>
#include <sdl_net.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include <sdl_image.h>

#include "TextureManager.h"
#include "TextManager.h"
#include "GameScreenManager.h"
#include "InputHandler.h"
#include "ParticleEngine.h"
#include "MainMenuScreen.h"
#include "MainGameScreen.h"
#include "LocalPlayer.h"
#include "AIPlayer.h"
class Game
{
	private:
		static Game* m_singleton;
		Game() {}
		int		m_width,
				m_height,
				m_depth;
		bool	m_hardware,
				m_fullscreen;

		Uint32 m_tick;

		bool SetupWindow();

		bool m_running;
		Uint32 m_lastUpdate;
		int	frames;
		int fps;
		InputHandler*	Input;
		TextManager*	TextMgr;
		GameScreenManager* ScreenManager;
		ParticleEngine*	Particles;
		bool Destroy();
	public:
		static Game* GetInstance();
		bool Initialize(int width, int height, int depth, bool hardware, bool fullscreen);
		void StartLoop();
		bool UpdateAll();
		bool BeginScene();
		bool DrawAll();
		bool EndScene();
		static bool ShutDown();
};

#define GAME Game::GetInstance()