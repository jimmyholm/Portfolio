#pragma once

#include <SFML/Window.hpp>
#include <unordered_map>
#include <memory>
#include "MessageTypes.h"
#include "MessageHandler.h"
class CMessageDispatch
{
	public:
		// Post a message to a handler, executing its "processMessage" function. Return false if no handler is registered to the given event.
		bool postMessage(const IMessage& Message);
		// Register a new handler for a message type, returns the old handler.
		IMessageHandler* registerHandler(const EMessageType& MessageType, IMessageHandler* Handler);
		// Retrieve the handler currently registered to a message type.
		IMessageHandler* getHandler(const EMessageType MessageType) const;
		// Remove the handler for a specific message type, return the old handler.
		IMessageHandler* removeHandler(const EMessageType& MessageType);
		// Clear all registered handlers
		void clear();
		// Get the singleton instance of the dispatcher.
		static CMessageDispatch& getInstance();

	private:
		std::unordered_map<EMessageType, IMessageHandler*> m_Handlers;
		CMessageDispatch();
		CMessageDispatch(CMessageDispatch&);
		CMessageDispatch& operator=(CMessageDispatch&);
};