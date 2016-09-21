#pragma once
#include "Utility.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "TextManager.h"
#include "ButtonManager.h"
#include <vector>

class DrawableList
{
	private:
		enum BTNID { BTN_UP = 1, BTN_DOWN};
		std::vector<std::string> Strings;				// The list actually holding the strings.
		Pos2D Position;									// The top left corner of the list (As opposed to the centre, for simplicity)
		Pos2D Size;										// The size of the list
		size_t NumEntries;								// Number of entries in list
		int Selected;									// -1 if no entry is selected.
		int First;										// First line to draw.
		size_t LinesToDraw;								// Maximum number of lines to draw
		int	 LineHeight;
		int	 MaxWidth;
		std::string Font;
		Texture* Background;
		bool DrawDividers;
		bool CanSelect;
		void init(std::string font, bool drawDividers, Pos2D pos, Pos2D size);
		DrawableList(void);
		ButtonManager* buttons;
	public:
		~DrawableList(void);
		static DrawableList* CreateList(std::string font, bool drawDividers, Pos2D pos, Pos2D size); // Create a list
		int Entries();									// Return the size of the list
		Pos2D GetSize();								// Get the dimensions of the list
		Pos2D GetPosition();							// Get the position of the list
		void AddString(std::string str);				// Add a string
		void InsertString(std::string str, size_t pos); // Insert a string, or add it at the end
		void RemoveString(size_t index);				// Remove a string from the list
		std::string GetString(size_t Index);			// Return string at index
		int GetSelected();								// Return the selected index
		std::string GetSelection();						// Return the selected string
		void Draw();									// Draw the list
		void NextPage();								// move to the next page of the list
		void PreviousPage();							// move to the previous page of the list
		void NextLine();								// Move one line forward
		void PreviousLine();							// Move one line backward
		void Update();									// Check for input and update the selection if necessary.
		void Destroy();
};