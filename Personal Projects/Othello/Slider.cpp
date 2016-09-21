#include "Slider.h"


Slider::Slider(void) : MaxValue(0), MinValue(0), Value(0), Width(0), Height(0), Position(Pos2D(0,0)), ID(0), Focus(false), Label("")
{
	OnChange = NULL;
}

Slider::~Slider(void)
{
}

void Slider::CreateSlider(Pos2D position, int width, int minvalue, int maxvalue, int defvalue, int id)
{
	Position = position;
	Width = width;
	MinValue = minvalue;
	MaxValue = maxvalue;
	Value = defvalue;
	if(Value < MinValue)
		Value = MinValue;
	if(Value > MaxValue)
		Value = MaxValue;
	Input = InputHandler::GetInstance();
	Height = 3;
	char txt[256];
	_itoa_s(Value, txt, 256, 10);
	Label = txt;
	ID = id;
}

void Slider::Update()
{
	Pos2D mousePos = Input->GetMousePosition();
	mousePos.x -= Position.x-(Width/2);
	if((float)Width/2.0 - Width/2 > 0)
		mousePos.x++;
	mousePos.y -= Position.y-2;
	if(Input->MouseDown(MOUSE_LEFT))
	{
		if(mousePos.x > 0 && mousePos.x < Width-1 && mousePos.y >= 0 && mousePos.y < Height)
			Focus = true;
		else
			Focus = false;
	}
	if(Input->MouseUp(MOUSE_LEFT) && Focus)
		Focus = false;

	if(Focus) // Only slide if the slider has focus (i.e. the slider has to be clicked -then- dragged
	{
		if(Input->MouseHeld(MOUSE_LEFT))
		{
				float f = (float)(mousePos.x) / (float)(Width); // percentage along the slider
				int NewValue = (int)(((float)(MaxValue)-(float)MinValue)*f + MinValue);
				if((((float)(MaxValue)-(float)MinValue)*f + MinValue) - NewValue > 0)
					NewValue++;
				if(NewValue < MinValue)
					NewValue = MinValue;
				if(NewValue > MaxValue)
					NewValue = MaxValue;
				Value = NewValue;
				char txt[256];
				_itoa_s(Value, txt, 256, 10);
				Label = txt;
				if(OnChange != NULL)
					OnChange->Call(ID);
		}
	}
}

void Slider::Draw()
{
	int NormalValue = Value - MinValue;	 //
	int NormalMax = MaxValue - MinValue; // These two values are used to decide ratio between current and max value
	// Print the value
	// Draw the indicator
	int IndicatorX = (int)(((float)NormalValue/(float)NormalMax) * (Width-1));
}

void Slider::Destroy()
{
	}

void Slider::SetValue(int value)
{
	Value = value;
	if(Value < MinValue)
		Value = MinValue;
	if(Value > MaxValue)
		Value = MaxValue;
	char txt[256];
	_itoa_s(Value, txt, 256, 10);
	Label = txt;
}

void Slider::AddOne()
{
	if(Value != MaxValue)
		Value++;
}

void Slider::DecOne()
{
	if(Value != MinValue)
		Value--;
}

void Slider::SetChangeFunc(TFunctor<int>* ChangeFunc)
{
	OnChange = ChangeFunc;
}