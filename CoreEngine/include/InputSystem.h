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

	virtual void attach(const EventID& _ID, EventSubscriber* subscriber) override;
	virtual void detach(const EventID& _ID, EventSubscriber* subscriber) override;
	virtual void notify(const EventID& _ID) override;

	static const EventID GameStateChanged;

	void Update();

private:
	Scene* _currentScene;
	sf::RenderWindow* _window;

	bool m_spacePressed = false;
};