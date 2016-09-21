#include "CSGameStateManager.h"
CSGameStateManager* CSGameStateManager::m_Instance = 0;
// Designate this as the next state. If a state is already decided, this returns false

CSGameStateManager::CSGameStateManager() : m_NextState(NULL)
{
}
bool CSGameStateManager::PushState(IGameState* State)
{
	if(m_NextState != NULL)
		return false;
	m_NextState = State;
	return true;
}
// Update the topmost state in the stack.
bool CSGameStateManager::Update(sf::Time TimeElapsed)
{
	if(m_StateStack.empty())
	{
		if(m_NextState != NULL)
		{
			m_StateStack.push(m_NextState);
			m_NextState = NULL;
		}
		else
			return false;
		return true;
	}
	bool Ret = false;	
	Ret = m_StateStack.top()->Update(TimeElapsed);
	if(m_StateStack.top()->IsDead())
	{
		m_StateStack.top()->Destroy();
		m_StateStack.pop();
	}
	if(m_NextState != NULL)
	{
		m_NextState->Initialize();
		m_StateStack.push(m_NextState);
		m_NextState = NULL;
	}
	return Ret;
}
// Draw the topmost state in the stack
bool CSGameStateManager::Draw(sf::RenderTarget& target, sf::RenderStates states)
{
	if(m_StateStack.empty())
		return false;
	bool Ret = false;
	Ret = m_StateStack.top()->Draw(target, states);
	return Ret;
}
// Loops through the strack, destroying and popping each one to free up all used memory.
bool CSGameStateManager::Destroy()
{
	while(!m_StateStack.empty())
	{
		m_StateStack.top()->Destroy();
		m_StateStack.pop();
	}
	return true;
}

CSGameStateManager* CSGameStateManager::GetInstance()
{
	if(m_Instance == NULL)
		m_Instance = new CSGameStateManager();
	return m_Instance;
}

void CSGameStateManager::Free()
{
	if(m_Instance != NULL)
	{
		m_Instance->Destroy();
		delete m_Instance;
		m_Instance = NULL;
	}
}