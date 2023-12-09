#include "InputSystem.h"
#include "iostream"
#include <Button.h>

const EventID InputSystem::GameStateChanged = "GameStateChanged";

sf::Clock g_DeltaTimeClock;
float g_DeltaTime;

InputSystem::InputSystem(sf::RenderWindow* window, Scene* currentScene) : _window(window), _currentScene(currentScene)
{
}

InputSystem::~InputSystem()
{
	this->_window = nullptr;
}

void InputSystem::attach(const EventID& _ID, EventSubscriber* subscriber)
{
	m_hashSubscribers[_ID].push_back(subscriber);
}

void InputSystem::detach(const EventID& _ID, EventSubscriber* subscriber)
{
	auto& subscribers = m_hashSubscribers[_ID];
	subscribers.erase(std::remove(subscribers.begin(), subscribers.end(), subscriber), subscribers.end());
}

void InputSystem::notify(const EventID& _ID)
{
	if (m_hashSubscribers.find(_ID) != m_hashSubscribers.end())
		for (auto subscriber : m_hashSubscribers[_ID])
		{
			EventBase* eventB = new EventBase(_ID);
			subscriber->onNotify(*eventB);
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
				notify("LeftClick");
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
