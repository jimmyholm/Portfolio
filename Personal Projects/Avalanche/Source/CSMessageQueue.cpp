#include "CSMessageQueue.h"

CSMessageQueue* CSMessageQueue::m_Instance = NULL;

CSMessageQueue* CSMessageQueue::GetInstance()
{
	if(m_Instance == NULL)
		m_Instance = new CSMessageQueue();
	return m_Instance;
}

void CSMessageQueue::DispatchMessages()
{
	while(m_MessageCount != 0)
	{
		IMessage* msg = m_MessageQueue.front();
		stdext::hash_map<unsigned long, IMessageHandler*>::iterator it = m_MessageHandlers.find(msg->m_MessageType);
		if(it != m_MessageHandlers.end())
			it->second->ReceiveMessage(msg);
		m_MessageQueue.pop();
		m_MessageCount--;
	}
}

void CSMessageQueue::RegisterHandler(IMessageHandler* Handler, unsigned long* Messages, size_t MessageCount)
{
	size_t cur = 0;
	size_t cnt = MessageCount;
	while(cnt > 0)
	{
		unsigned long index = *(Messages+cur);
		m_MessageHandlers[index] = Handler;
		cnt--;
		cur++;
	}
}

void CSMessageQueue::RemoveHandler(unsigned long* Messages, size_t MessageCount)
{
	size_t cur = 0;
	size_t cnt = MessageCount;
	while(cnt > 0)
	{
		unsigned long index = *(Messages+cur);
		if(m_MessageHandlers.find(index) != m_MessageHandlers.end())
		{
			m_MessageHandlers.erase(index);
		}
		cnt--;
		cur++;
	}
}


void CSMessageQueue::Clear()
{
	while(m_MessageCount != 0)
	{
		IMessage* msg = m_MessageQueue.front();
		m_MessageQueue.pop();
		delete msg;
		m_MessageCount--;
	}

	stdext::hash_map<unsigned long, IMessageHandler*>::iterator it = m_MessageHandlers.begin();
	while(it != m_MessageHandlers.end())
	{
		it->second->Clear();
		it++;
	}
	m_MessageHandlers.clear();
	delete m_Instance;
	m_Instance = NULL;
}