#pragma once
#include "InputHandler.h"
#include "Button.h"

#include <vector>

#define NO_BUTTON -1

class ButtonManager
{
	private:
		std::vector<Button*> Buttons;
		size_t NumButtons;
		InputHandler* Input;
	public:
		ButtonManager(void);
		~ButtonManager(void);
		void	AddButton(Button* button);		// Add a button
		int		Update();						// Returns either -1 if no button was pressed, or the return-value of the pressed button.
		void	DestroyButton(size_t index);	// Destroy the given button
		void	DestroyManager();				// Destroy the entire manager
		void	Draw();
};
