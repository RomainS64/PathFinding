#pragma once
#include "SceneObject.h"
#include <list>
#include <SFML/Graphics.hpp>

class Scene
{
public:
	Scene(sf::RenderWindow* renderWindows, std::list<SceneObject*> sceneObjects);

	void Start();
	void Update();
	void Draw();

	~Scene();

private:
	sf::RenderWindow* _renderWindows;
	std::list<SceneObject*> _sceneObjects;

};

