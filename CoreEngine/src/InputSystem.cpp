#include "InputSystem.h"
#include "iostream"
#include <Button.h>

const EventID InputSystem::GameStateChanged = "GameStateChanged";

sf::Clock g_DeltaTimeClock;
float g_DeltaTime;

InputSystem::InputSystem(sf::RenderWindow* window) : _window(window)
{
}

InputSystem::~InputSystem()
{
	this->_window = nullptr;
}

void InputSystem::Attach(const EventID& _ID, EventSubscriber* subscriber)
{
	_hashSubscribers[_ID].push_back(subscriber);
}

void InputSystem::Detach(const EventID& _ID, EventSubscriber* subscriber)
{
	auto& subscribers = _hashSubscribers[_ID];
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void InputSystem::Notify(const EventID& _ID)
{
	if (_hashSubscribers.find(_ID) != _hashSubscribers.end())
		for (auto subscriber : _hashSubscribers[_ID])
		{
			EventBase* eventB = new EventBase(_ID);
			subscriber->OnNotify(*eventB);
		}
}

void InputSystem::Update()
{
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window->close();

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				Notify("LeftClick");
			}
		}
		if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)
			m_spacePressed = false;
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				// TODO: Exit the game
			}
			else if (event.key.code == sf::Keyboard::Space)
			{
				// TODO: Import main.cpp code here
				m_spacePressed = true;
			}
		}
	}
}
