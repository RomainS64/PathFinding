#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <functional>

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
	using CallbackFunction = std::function<void()>;

	EventSubscriber() {};
	virtual ~EventSubscriber() {};
	virtual void onNotify(const EventBase& _eventB) = 0;
	void subscribe(CallbackFunction callback) { _callbacks.push_back(callback); };

protected:
	std::vector<CallbackFunction> _callbacks;
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



