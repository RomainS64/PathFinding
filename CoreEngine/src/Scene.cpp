#include "Scene.h"

Scene::Scene(sf::RenderWindow* renderWindows, std::list<SceneObject*> sceneObjects):
	_renderWindows(renderWindows),
	_sceneObjects(sceneObjects)
{}

void Scene::Start()
{
	for (SceneObject* sceneObject : _sceneObjects)
	{
		sceneObject->Start();
	}
}

void Scene::Update()
{
	for (SceneObject* sceneObject : _sceneObjects)
	{
		sceneObject->Update();
	}
}

void Scene::Draw()
{
	_renderWindows->clear();
	for (SceneObject* sceneObject : _sceneObjects)
	{
		sceneObject->Draw();
	}
	_renderWindows->display();
}

Scene::~Scene()
{
	for (const SceneObject* sceneObject : _sceneObjects) 
	{
		delete sceneObject;
	}
}
