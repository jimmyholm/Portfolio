#pragma once

#include <SDL_Net.h>
#include <SDL.h>

class TCPConnection
{
	protected:

	public:

		bool OpenSocket(char* Hostname, short Port);
		void OpenSocket(TCPsocket socket);
		bool CloseSocket();
		bool HasData();
		void Listen();
		TCPsocket GetSocket();
		// Packet GetData;

};