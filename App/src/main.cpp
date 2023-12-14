#include <chrono>
#include <iostream>
#include <thread>
#include <vector>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Scene.h"
#include "Square.h"
#include "AStarBoard.h"
#include "AStar.h"
#include <InputSystem.h>
#include <Button.h>
#include "Event.h"

#include <filesystem>

#include "AStarBoardEditor.h"
#include "Sprite.h"


int main()
{
	
	sf::RenderWindow window(sf::VideoMode(1920 / 2, 1080 / 2), "PathFinding");
	window.setFramerateLimit(60);
	InputSystem* inputSystem = new InputSystem(&window);
	//Ressources
	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("../../Assets/gamefont.ttf"))
	{
		std::cout << "Unable to load font.";
	}
	sf::Texture* debugTexture = new sf::Texture();
	if (!debugTexture->loadFromFile("../../Assets/Title.png"))
	{
		std::cout << "Unable to load texture.";
	}

	// Button stuff
	Sprite* title = new Sprite(&window, debugTexture, sf::Vector2f(0.2, 0.1), sf::Vector2f(0.6, 0.6));
	Button* menuButton = new Button(&window, sf::Vector2f(0.4, 0.4), sf::Vector2f(0.2f, 0.07f), sf::Text("Start Game", *font), sf::Color(100, 100, 100), sf::Color::White);
	std::list<SceneObject*> menuObjects;
	menuObjects.push_back(menuButton);
	menuObjects.push_back(title);
	Scene* menuScene = new Scene(&window, menuObjects);
	Scene* currentScene = menuScene;
	
	AStarBoard* board = new AStarBoard(&window, sf::Vector2f(0.15f, 0.1f), sf::Vector2i(16, 9), 0.7f);
	AStarBoardEditor* editor = new AStarBoardEditor(&window,inputSystem,board,font);
	std::list<SceneObject*> sceneObjects;
	
	
	sceneObjects.push_back(editor);
	sceneObjects.push_back(board);
	Scene* gameScene = new Scene(&window, sceneObjects);
	
	inputSystem->Attach("LeftClick",menuButton);
	bool isInGameScene = false;
	menuButton->Subscribe([&currentScene, gameScene,&isInGameScene]()
	{
		if(isInGameScene)return;
		isInGameScene = true;
		gameScene->Start();
		currentScene = gameScene;
	});
	
	while (window.isOpen())
	{
		
		currentScene->Update();
		currentScene->Draw();
		inputSystem->Update();
	}
	delete menuScene;
	delete gameScene;
	delete inputSystem;
	delete font;
	delete debugTexture;
	return 0;
}
