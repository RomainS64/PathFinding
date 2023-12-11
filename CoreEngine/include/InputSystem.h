#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"
#include "Event.h"
#include "Scene.h"

/**
*
*/
class InputSystem : public EventPublisher
{
public:
	InputSystem(sf::RenderWindow* window);
	~InputSystem();

	virtual void Attach(const EventID& _ID, EventSubscriber* subscriber) override;
	virtual void Detach(const EventID& _ID, EventSubscriber* subscriber) override;
	virtual void Notify(const EventID& _ID) override;

	static const EventID GameStateChanged;

	void Update();

private:
	sf::RenderWindow* _window;

	bool m_spacePressed = false;
};