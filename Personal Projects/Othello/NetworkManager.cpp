#include "NetworkManager.h"

NetworkManager* NetworkManager::Instance = 0;

NetworkManager* NetworkManager::GetInstance()
{
	if(Instance == 0)
		Instance = new NetworkManager();
	return Instance;
}
NetworkManager::NetworkManager()
{
}