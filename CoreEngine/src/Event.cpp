#include "Event.h"

void EventPublisher::Attach(const EventID& _ID, EventSubscriber* subscriber)
{
	_hashSubscribers[_ID].push_back(subscriber);
}

void EventPublisher::Detach(const EventID& _ID, EventSubscriber* subscriber)
{
	// TODO: Implement Detach
}

void EventPublisher::Notify(const EventID& _ID)
{
	// TODO: Implement Notify
}
