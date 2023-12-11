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
	virtual void OnNotify(const EventBase& _eventB) = 0;
	void Subscribe(CallbackFunction callback) { _callbacks.push_back(callback); };

protected:
	std::vector<CallbackFunction> _callbacks;
};

class EventPublisher
{
public:
	EventPublisher() {};
	virtual ~EventPublisher() {};

	virtual void Attach(const EventID& _ID, EventSubscriber* subscriber);
	virtual void Detach(const EventID& _ID, EventSubscriber* subscriber);
	virtual void Notify(const EventID& _ID);

protected:
	std::unordered_map< EventID, std::vector<EventSubscriber*> > _hashSubscribers;
};



