#ifndef SFMLG_IGAMESTATE_H
#define SFMLG_IGAMESTATE_H
#include "IMessageHandler.h"
#include <SFML\Graphics.hpp>
class CSGameStateManager; // Forward declaration of the manager; so that the game-states can pop and push new states
						// from and to the gamestate manager

enum eSubState // Substates define the different states of the gamestate; whether we're transitioning between states, if we're active
{			  // or if we're paused, The last one, "SS_DEAD", signifies that we should remove the state next frame
	SS_TRANSITION_IN,
	SS_ACTIVE,
	SS_PAUSED,
	SS_TRANSITION_OUT,
	SS_DEAD
};

class IGameState : public IMessageHandler
{
	// The GameState class is where logic takes place. It takes care of initializing, updating, drawing and destroying
	// items relevant for any given state of the game.
	// The GameState class serves as a base-class for specific state implementations
	protected:
		CSGameStateManager*	m_StateManager; // This is the state-manager responsible for popping and pushing states
		eSubState			m_SubState;		// The active substate of the gamestate.
	public:
		virtual bool Initialize() = 0; // Initialize the game state
		virtual bool Update(sf::Time TimeElapsed) = 0; // Update the game logic based on the tick-delta
		virtual bool Draw(sf::RenderTarget& target, sf::RenderStates states) = 0; // Draw the relevant graphics to the given surface
		virtual bool Destroy() = 0; // Destroy the game state and free all its allocated memory

		// Simple state-handling functions
		bool IsDead() { return m_SubState == SS_DEAD; }
		eSubState GetSubState() { return m_SubState; }
		void SetSubState(eSubState newSubState) { m_SubState = newSubState; }
};

#endif