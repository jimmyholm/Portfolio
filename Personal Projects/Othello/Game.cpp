#include "Game.h"
#include <exception>
#include <time.h>


Game* Game::m_singleton = 0;

Game* Game::GetInstance()
{
	if(m_singleton == 0)
		m_singleton = new Game;
	return m_singleton;
}

bool Game::Initialize(int width, int height, int depth, bool hardware, bool fullscreen)
{
	char f = GetSenderID(0xA0);
	srand((unsigned int)time(0));
	// Initialize all the subsystem and break on failure
	if(SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		throw(std::exception("Failed to initialize SDL!"));
		return false;
	}
	if(Mix_Init(MIX_INIT_OGG) == 0)
	{
		SDL_Quit();
		throw(std::exception("Failed to initialize SDL_Mixer!"));
		return false;
	}
	if(SDLNet_Init() != 0)
	{
		Mix_Quit();
		SDL_Quit();
		throw(std::exception("Failed to initialize SDL_Net!"));
		return false;
	}

	int res = IMG_Init(IMG_INIT_TIF);
	if((res&IMG_INIT_TIF) != IMG_INIT_TIF)
	{
		SDLNet_Quit();
		Mix_Quit();
		SDL_Quit();
		throw(std::exception("Failted to initialize SDL_Image!"));
		return false;
	}
	
	// Set the window dimensions and necessary information
	m_width = width;
	m_height = height;
	m_depth = depth; // Note: ignored, always 32
	m_hardware = hardware; // Note: ignored, always true
	m_fullscreen = fullscreen;
	srand(0);
	// Setup our window and break on failure.
	if(!SetupWindow())
		return false;
	// Disable backface culling
	glDisable(GL_CULL_FACE);
	Input = InputHandler::GetInstance();
	ScreenManager = GameScreenManager::GetInstance();
	TextMgr = TextManager::GetInstance();
	// Load our fonts
	TextMgr->LoadFont("FreeSerif12", "FreeSerifBold.ttf", 12);
	TextMgr->LoadFont("FreeSerif25", "FreeSerifBold.ttf", 25);
	Particles = ParticleEngine::GetInstance();
	// Load particle textures on startup
	TextureMgr->LoadTexture("Particle", "Gfx/Particle.tga");
	TextureMgr->LoadTexture("Confetti", "Gfx/Confetti.tga");
	// Load the interface textures
	TextureMgr->LoadScript("Interface", "Interface.txt");
	if(glExtensionAvailable("GL_EXT_draw_range_elements"))
		pglDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)wglGetProcAddress("glDrawRangeElements");
	// Check for VBO support and if it exists, alert the texture manager and grab the necessary function pointers.
	if(glExtensionAvailable("GL_ARB_vertex_buffer_object") && pglDrawRangeElements != 0)
	{
		pglGenBuffersARB = (PFNGLGENBUFFERSARBPROC)wglGetProcAddress("glGenBuffersARB");
		pglBindBufferARB = (PFNGLBINDBUFFERARBPROC)wglGetProcAddress("glBindBufferARB");
		pglBufferDataARB = (PFNGLBUFFERDATAARBPROC)wglGetProcAddress("glBufferDataARB");
		pglDeleteBuffersARB = (PFNGLDELETEBUFFERSARBPROC)wglGetProcAddress("glDeleteBuffersARB");
		
		if(pglGenBuffersARB != 0 && pglBindBufferARB != 0 && pglBufferDataARB != 0 && pglDeleteBuffersARB != 0)
			TextureMgr->UseVBO(true);
		else
		{
			MessageBox(0, "Found 'GL_ARB_vertex_buffer_object' extension but failed to accquire function pointers. Falling back to safemode.", "Error", MB_ICONINFORMATION|MB_OK);
		}
	}
	// Push the main-menu screen onto the game-screen stack.
	MainMenuScreen* MainMenu = new MainMenuScreen;
	ScreenManager->PushScreen(MainMenu);
	return true;	
}

bool Game::SetupWindow()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	Uint32 flags = SDL_OPENGL | SDL_HWSURFACE | SDL_SRCALPHA;
	if(m_fullscreen)
		flags |= SDL_FULLSCREEN;
	if(SDL_SetVideoMode(m_width, m_height, 32, flags) == NULL)
	{
		IMG_Quit();
		SDLNet_Quit();
		Mix_Quit();
		SDL_Quit();
		throw(std::exception("Failed to set video mode!"));
		return false;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0,m_width,m_height,0, -1.0f, 1.0f);
	glClearColor(.39f, .58f, .93f, 1.0f);
	m_tick = SDL_GetTicks();
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	m_running = true;
	m_lastUpdate = 0;
	SDL_WM_SetCaption("Foxy Othello", "Othello.ico");
	return true;
}

bool Game::ShutDown()
{
	bool ret = m_singleton->Destroy();
	delete m_singleton;
	return ret;
}
bool Game::Destroy()
{
	Particles->Destroy();
	ScreenManager->ShutDown();
	TextureMgr->ReleaseAll();
	TextureMgr->Destroy();
	TextMgr->ShutDown();
	IMG_Quit();
	SDLNet_Quit();
	Mix_Quit();
	SDL_Quit();
	return true;
}

void Game::StartLoop()
{
	while(m_running == true)
	{
		UpdateAll();
		BeginScene();
		DrawAll();
		EndScene();
	}
	Game::ShutDown();
}

bool Game::UpdateAll()
{
	Uint32 curTick, tickDelta;
	curTick = SDL_GetTicks();
	tickDelta = curTick - m_tick;
	m_tick = curTick;
	SDL_Event e;
	SDL_PollEvent(&e);
	if(e.type == SDL_QUIT)
		m_running = false;
	Input->OneFrame(curTick);
	TextMgr->UpdateAll(tickDelta);
	Particles->UpdateAll(tickDelta);
	ScreenManager->OneFrame(tickDelta);
	if(ScreenManager->CountScreens() == 0)
		m_running = false;
	return true;
}

bool Game::BeginScene()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool Game::DrawAll()
{
	ScreenManager->Render();
	Particles->Draw();
	TextMgr->DrawAll();
	TextureMgr->DrawAll();
	if(!exceptionError())
		return false;
	return true;
}

bool Game::EndScene()
{
	SDL_GL_SwapBuffers();
	TextMgr->DestroyDead();
	return true;
}