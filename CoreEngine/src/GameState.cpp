#include "GameState.h"
#include "iostream"

const EventID GameState::GameStateChanged = "GameStateChanged";

sf::Clock g_DeltaTimeClock;
float g_DeltaTime;

void GameState::Initialize()
{
	_currentScene->Start();
}

void GameState::OnWindowEvent(const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed)
	{
	}
	else if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Escape)
		{
			// TODO: Exit the game
		}
		else if (event.key.code == sf::Keyboard::Space)
		{
			// TODO: Import main.cpp code here
		}
	}
}

void GameState::Update()
{
	g_DeltaTime = g_DeltaTimeClock.restart().asSeconds();
	sf::Time elapsed = m_clock.restart();

	if (m_timeEvents >= 0)
	{
		m_timeEvents -= elapsed.asSeconds();
		if (m_timeEvents <= 0)
		{
			// create a random event fake
		}
	}

	_currentScene->Update();
}

void GameState::Draw(sf::RenderWindow* renderWindow)
{
	_currentScene->Draw();
}
