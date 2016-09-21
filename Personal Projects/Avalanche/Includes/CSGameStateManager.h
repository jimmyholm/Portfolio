#ifndef SFMLG_CSGAMESTATEMANAGER_H
#define SFMLG_CSGAMESTATEMANAGER_H

#include <stack>
#include "IGameState.h"
class CSGameStateManager
{
	// The game state manager is responsible for managing the game states.
	// The Notris game has four distinct game-states, Main Menu, Highscore, Game and Game Over
	private:
		std::stack<IGameState*> m_StateStack;	// Store our states in a stack (LIFO container). The topmost state is the only relevant
		IGameState*				m_NextState;	// This is the next state to be pushed on the stack. The state is pushed after the next
												// update sequence.
		CSGameStateManager();					// Hidden constructor - singleton
		static CSGameStateManager* m_Instance;	// The instance of the singleton
	public:
		bool PushState(IGameState* State);	// Designate this as the next state. If a state is already decided, this returns false
		bool Update(sf::Time TimeElapsed); // Update the topmost state in the stack.
		bool Draw(sf::RenderTarget& target, sf::RenderStates states); // Draw the topmost state in the stack
		bool Destroy(); // Loops through the strack, destroying and popping each one to free up all used memory.
		static CSGameStateManager* GetInstance();
		static void Free(); // Destroy the instance
};
#endif