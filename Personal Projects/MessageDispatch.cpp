#include "MessageDispatch.h"
#include <cassert>

CMessageDispatch::CMessageDispatch(){}
CMessageDispatch::CMessageDispatch(CMessageDispatch&){}
CMessageDispatch& CMessageDispatch::operator=(CMessageDispatch&){ return *this; }

CMessageDispatch& CMessageDispatch::getInstance()
{
	static CMessageDispatch instance;
	return instance;
}

bool CMessageDispatch::postMessage(const IMessage& Message)
{
	if (m_Handlers.find(Message.m_MessageType) == m_Handlers.end())
		return false;
	m_Handlers[Message.m_MessageType]->processMessage(Message);
	return true;
}

IMessageHandler* CMessageDispatch::getHandler(const EMessageType MessageType) const
{
	auto it = m_Handlers.find(MessageType);
	if (it == m_Handlers.end())
		return nullptr;
	return (*it).second;
}

IMessageHandler* CMessageDispatch::registerHandler(const EMessageType& MessageType, IMessageHandler* Handler)
{
	IMessageHandler* ret;
	if (m_Handlers.find(MessageType) == m_Handlers.end())
		ret = nullptr;
	else
		ret = m_Handlers[MessageType];
	m_Handlers[MessageType] = Handler;
	return ret;
}

IMessageHandler* CMessageDispatch::removeHandler(const EMessageType& MessageType)
{
	auto it = m_Handlers.find(MessageType);
	if ( it == m_Handlers.end())
		return nullptr;
	IMessageHandler* ret = m_Handlers[MessageType];
	m_Handlers.erase(it);
	return ret;
}

void CMessageDispatch::clear()
{
	m_Handlers.clear();
}