#include "GameScreen.h"
#include "GameScreenManager.h"
#include "EditBox.h"
#include "AnimationManager.h"
#include "Sprite.h"
#include "TextureFade.h"
#include "MainGameScreen.h"

enum {SELECTION_HOST = 0, SELECTION_JOIN, SELECTION_EXIT};

class MainMenuScreen : public GameScreen
{
	protected:
		Pos2D	 HostPos, JoinPos, ExitPos; // Draw-Positions for the textures.
		Texture* HostGame[2];	// Selected/Deselected "Host Game" textures
		Texture* JoinGame[2];	// Selected/Deselected "Join Game" textures
		Texture* Exit[2];		// Selected/Deselected "Exit Game" textures
		Texture* Background;	// Background texture
		int		 Selection;		// Currently selected option
		int		 RepeatDelay;	// Added to each update and checked for proper key-repeat delays
		MainGameScreen* mGame;
	public:
		MainMenuScreen();
		virtual bool Update(Uint32 TickDelta); // Return false if this screen should be popped
		virtual void Draw();
		virtual void Destroy(); // De-initialize the screem; called when the screen is popped
};