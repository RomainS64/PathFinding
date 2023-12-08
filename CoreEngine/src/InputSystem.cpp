#include "InputSystem.h"
#include "iostream"

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

void InputSystem::attach(const EventID& _ID, EventSubscriber* subscriber)
{
	// TODO: Add the subscriber to the list of subscribers for the given event
}

void InputSystem::detach(const EventID& _ID, EventSubscriber* subscriber)
{
	// TODO: Remove the subscriber from the list of subscribers for the given event
}

void InputSystem::notify(const EventID& _ID)
{
	// TODO: Notify all subscribers of the given event
}

void InputSystem::Update()
{
	sf::Event event;
	while (_window->pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			_window->close();
		// Check if the space bar is pressed

		if (event.type == sf::Event::MouseButtonPressed)
		{
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
