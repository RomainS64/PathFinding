#pragma once
#include <SFML/Graphics.hpp>
class SceneObject
{
public:
	SceneObject(sf::RenderWindow* renderWindows, sf::Vector2f position);
	virtual void Start();
	virtual void Update();
	virtual void Draw();
	virtual bool Contains(sf::Vector2i position) = 0;
	virtual ~SceneObject();

protected:
	sf::RenderWindow* _renderWindows;
	sf::Vector2f _position;
};

