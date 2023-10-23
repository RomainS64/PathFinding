#pragma once
#include <SFML/Graphics.hpp>
class SceneObject
{
public:
	SceneObject(sf::RenderWindow* renderWindows);
	virtual void Start();
	virtual void Update();
	virtual void Draw();

	~SceneObject();

private:
	sf::RenderWindow* _renderWindows;

};

