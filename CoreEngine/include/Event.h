#pragma once

#include <string>
#include <vector>
#include <unordered_map>

using EventID = std::string;

class EventBase
{
public:
	EventBase(const EventID& id) : _id(id) {};
	virtual ~EventBase() {};

	EventID _id;
};

class EventSubscriber
{
public:
	virtual void update(const EventBase* _eventB) = 0;
};

class EventPublisher
{
public:
	EventPublisher() {};
	virtual ~EventPublisher() {};

	virtual void attach(const EventID& _ID, EventSubscriber* subscriber);
	virtual void detach(const EventID& _ID, EventSubscriber* subscriber);
	virtual void notify(const EventID& _ID);

protected:
	std::unordered_map< EventID, std::vector<EventSubscriber*> > m_hashSubscribers;
};



