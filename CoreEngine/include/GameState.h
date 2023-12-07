#pragma once

#include "SFML/Graphics.hpp"
#include "SFML/System/Clock.hpp"
#include "Observer.h"
#include "Scene.h"

/**
* Dans la logique de mon inspiration cette classe ressemble fortement à la Scene (tu me diras si je me trompe)
* Si c'est le cas déplacer la logique là bas.
*/
class GameState : public Subject
{
public:

	static const EventID GameStateChanged;

	void Initialize();

	void OnWindowEvent(const sf::Event& event);
	void Update();
	void Draw(sf::RenderWindow* renderWindow);

	inline bool IsDebugMode() const { return m_bDebugMode; }
private:
	Scene* _currentScene;

	bool        m_bDebugMode = false;
	sf::Clock   m_clock;
	float       m_timeEvents = 0;
};