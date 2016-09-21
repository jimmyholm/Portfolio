#include "GameScreenManager.h"
#include "GameScreen.h"
#include "EditBox.h"
#include "CheckBox.h"
#include "ButtonManager.h"
#include "TextManager.h"

class HostGameScreen : public GameScreen
{
	protected:
		CheckBox* LocalGame;
		CheckBox* RemoteGame; // Disabled
		CheckBox* AIwhite;
		CheckBox* AIblack;
		EditBox* PlayerName;
		ButtonManager* Buttons;
		TextManager* TxtMgr;
	public:
		void Setup();
		bool Update(Uint32 TickDelta);
		void Draw();
		void Destroy();
};