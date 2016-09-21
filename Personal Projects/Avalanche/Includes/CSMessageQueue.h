#ifndef SFMLG_CSMESSAGEQUEUE_H
#define SFMLG_CSMESSAGEQUEUE_H
#include "IMessage.h"
#include "IMessageHandler.h"
#include <hash_map>
#include <queue>
// Message Queue singleton. Receives and dispatches messages to handlers every frame.
class CSMessageQueue
{
	private:
		// Associate message handlers with the message-types they handle.
		stdext::hash_map<unsigned long, IMessageHandler*> m_MessageHandlers;
		// Keep a queue of every single message posted in the last frame.
		std::queue<IMessage*> m_MessageQueue;
		// Keep a counter of how many messages we've got, for rapidly deciding whether there are any messages to dispatch.
		size_t m_MessageCount;

		// Instance pointer, this is a singleton class.
		static CSMessageQueue* m_Instance;
		CSMessageQueue() : m_MessageCount(0) {}
	public:
		// Retrieve a pointer to the singleton instance
		static CSMessageQueue* GetInstance();

		// PostMessage takes an IMessage and puts it on the message queue.
		inline void PostMessage(IMessage* Message) { m_MessageQueue.push(Message); m_MessageCount++; }

		// DispatchMessages goes through the queue of messages, putting them onto the relevant message handlers and clearing the internal message queue.
		void DispatchMessages();

		// RegisterHandler takes a handler and a list of unsigned longs; a single handler can handle multiple event types. Collisions overwrite the previous handler.
		void RegisterHandler(IMessageHandler* Handler, unsigned long* Messages, size_t MessageCount);

		// RemoveHandler takes a list of messages and removes the current handler to them. Does not assume responsibility of the IMessageHandler pointer which is NOT freed.
		void RemoveHandler(unsigned long* Messages, size_t MessageCount);
		// Clear deletes all messages currently in the queue, and makes sure each message handler clears its own queue.
		void Clear();
};
#endif // SFMLG_CSMESSAGEQUEUE_H