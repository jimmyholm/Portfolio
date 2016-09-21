#include "ButtonManager.h"

ButtonManager::ButtonManager(void) : NumButtons(0)
{
	Input = InputHandler::GetInstance();
}

ButtonManager::~ButtonManager(void)
{
}

void ButtonManager::AddButton(Button* button)
{
	Buttons.push_back(button);
	NumButtons++;
}

int ButtonManager::Update()
{
	for(size_t i= 0; i < Buttons.size(); i++)
		Buttons[i]->Update();
	if(Input->MouseDown(MOUSE_LEFT))
	{
		for(size_t i = 0; i < NumButtons; i++)
		{
			if(Buttons[i]->PosOver(Input->GetMousePosition()))
			{
				return Buttons[i]->ButtonPressed();
			}
		}
	}
	return NO_BUTTON;
}

void ButtonManager::DestroyButton(size_t index)
{
	if(index >= 0 && index < NumButtons)
	{
		Buttons[index]->Destroy();
		delete Buttons[index];
		Buttons.erase(Buttons.begin() + index);
		NumButtons--;
	}
}

void ButtonManager::DestroyManager()
{
	for(size_t i = 0; i < NumButtons; i++)
	{
		Buttons[i]->Destroy();
	}
	NumButtons = 0;
	Buttons.clear();
}

void ButtonManager::Draw()
{
	for(size_t i = 0; i < NumButtons; i++)
		Buttons[i]->Draw();
}