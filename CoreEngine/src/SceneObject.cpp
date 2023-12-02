#include "SceneObject.h"
#include <iostream>

SceneObject::SceneObject(sf::RenderWindow* renderWindows, sf::Vector2f position):_renderWindows(renderWindows),_position(position){}

void SceneObject::Start()
{
	std::cout << "Starting Scene Object" << std::endl;
}

void SceneObject::Update()
{
	std::cout << "Updating Scene Object" << std::endl;
}

void SceneObject::Draw()
{
	std::cout << "Drawing Scene Object" << std::endl;
}

SceneObject::~SceneObject()
{
	std::cout << "Deleting Scene Object" << std::endl;
}
