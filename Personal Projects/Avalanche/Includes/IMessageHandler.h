#ifndef SFMLG_IMESSAGEHANDLER_H
#define SFMLG_IMESSAGEHANDLER_H
#include "IMessage.h"
#include <queue>
class CSMessageQueue;
// The IMessageHandler class contains its own message queue, containing nothing but relevant messages. It also contains one concrete function - ReceiveMessage - and one abstract function ProcessMessages.
// ProcessMessages is defined by the derived class, and it must loop through the entire message queue and meaningfully clear the queue, handling each message in turn.
class IMessageHandler
{
	protected:
		friend CSMessageQueue;
		// The Message queue member holds ONLY relevant messages, and nothing should in general be added directly, but the queue should be populated only through the receive message function.
		std::queue<IMessage*> m_MessageQueue;
		
		// Add a message to the queue. It's assumed the message is valid for this handler.
		inline void ReceiveMessage(IMessage* Message) { m_MessageQueue.push(Message); }

		// Clear deletes everything currently in the message queue, used to clean-up everything during shutdown.
		void Clear()
		{
			while(!m_MessageQueue.empty())
			{
				IMessage* msg = m_MessageQueue.front();
				m_MessageQueue.pop();
				delete msg;
			}
		}

		// Get the topmost message, or NULL if no messages exist.
		inline IMessage* GetTop()
		{
			if(m_MessageQueue.empty())
				return NULL;
			IMessage* ret = m_MessageQueue.front();
			m_MessageQueue.pop();
			return ret;
		}

		// The derived classes define this member function, which needs to loop through the queue and handle each message in turn. The handler is responsible for deleting the message once handled.
		virtual void ProcessMessages() = 0;
};

#endif // SFMLG_IMESSAGEHANDLER_H