#include "Event.h"

void EventPublisher::attach(const EventID& _ID, EventSubscriber* subscriber)
{
	m_hashSubscribers[_ID].push_back(subscriber);
}

void EventPublisher::detach(const EventID& _ID, EventSubscriber* subscriber)
{
	// TODO: Implement detach
}

void EventPublisher::notify(const EventID& _ID)
{
	// TODO: Implement notify
}
