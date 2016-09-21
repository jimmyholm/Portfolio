#pragma once
#include "Utility.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Functor.h"

class NewGameScreen;

class Slider
{
	int MaxValue;
	int MinValue;
	int Value;	// The value - should be something like int or float
	int Width;	// The width of the slider
	int Height; // Always 3
	Pos2D Position; // The center-position of the slider
	InputHandler* Input;
	std::string Label;
	int ID;
	bool Focus;
	
	TFunctor<int>* OnChange;
	public:
		Slider(void);
		~Slider(void);

		void CreateSlider(Pos2D position, int width, int minvalue, int maxvalue, int defvalue, int id = 0);

		int GetValue() { return Value;} // Return the value

		void Update();

		void Draw();

		void Destroy();

		void SetValue(int value);

		void AddOne();

		void DecOne();

		void SetChangeFunc(TFunctor<int>* ChangeFunc);

		int GetID() { return ID; }
};
