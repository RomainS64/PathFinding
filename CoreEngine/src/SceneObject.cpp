#include "SceneObject.h"
#include <iostream>

SceneObject::SceneObject(sf::RenderWindow* renderWindows):_renderWindows(renderWindows)
{}

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
