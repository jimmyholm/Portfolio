#ifndef SFMLG_IMESSAGE_H
#define SFMLG_IMESSAGE_H
#include "EMessageTypes.h"
// Abstract interface for a message type - all concrete messages derive from this base class, to allow a generic and uniform way of handling messages.
class IMessage
{
	public:
		// The m_MessageType member is used to distinguish between different types of messages. This should be an enumed value, for simplicity's sake. (Defined in EMEssageTypes.h)
		unsigned long m_MessageType;
};
#endif // SFMLG_IMESSAGE