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

class Observer
{
public:
	virtual void update(const EventBase* _eventB) = 0;
};

class Subject
{
public:
	virtual void attach(const EventID& _ID, Observer* observer);
	virtual void detach(const EventID& _ID, Observer* observer);
	virtual void notify(const EventID& _ID);

protected:
	std::unordered_map< EventID, std::vector<Observer*> > m_hashObserver;
};



