#include <chrono>
#include <iostream>
#include <thread>

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

#include <filesystem>

#include "Sprite.h"


void SetupProject(AStarBoard* board, Scene* scene)
{
    scene->Start();
    board->SetCellType(sf::Vector2i(1,0),Wall);
    board->SetCellType(sf::Vector2i(1,1),Wall);
    board->SetCellType(sf::Vector2i(1,2),Wall);
    board->SetCellType(sf::Vector2i(1,3),Wall);
    board->SetCellType(sf::Vector2i(3,8),Wall);
    board->SetCellType(sf::Vector2i(3,7),Wall);
    board->SetCellType(sf::Vector2i(3,6),Wall);
    board->SetCellType(sf::Vector2i(3,5),Wall);
    board->SetCellType(sf::Vector2i(3,4),Wall);
    board->SetCellType(sf::Vector2i(4,7),Wall);
    board->SetCellType(sf::Vector2i(6,7),Wall);
    board->SetCellType(sf::Vector2i(7,1),Wall);
    board->SetCellType(sf::Vector2i(7,2),Wall);
    board->SetCellType(sf::Vector2i(7,3),Wall);
    board->SetCellType(sf::Vector2i(7,4),Wall);
    board->SetCellType(sf::Vector2i(7,5),Wall);
    board->SetCellType(sf::Vector2i(7,6),Wall);
    board->SetCellType(sf::Vector2i(7,7),Wall);
    board->SetCellType(sf::Vector2i(5,7),Wall);
    board->SetCellType(sf::Vector2i(7,7),Wall);
    board->SetCellType(sf::Vector2i(8,7),Wall);
    board->SetCellType(sf::Vector2i(9,7),Wall);
    
    board->SetCellType(sf::Vector2i(0,0),Start);
    board->SetCellType(sf::Vector2i(8,8),End);
    board->SetCellType(sf::Vector2i(12,1),Checkpoint);
    board->CreatePortal(sf::Vector2i(5,5),sf::Vector2i(13,5));
    board->ValidateCells(); 
}
std::vector<Node*> CalculatePath(AStarBoard* board)
{
	AStar* astar = new AStar(*board);
	Node* aStarStart = board->startNode;
	std::vector<Node*> path;
	for (auto checkpoint : board->checkpoints)
	{
		std::vector<Node*> findedPath = astar->findPath(aStarStart, checkpoint);
		path.insert(path.end(), findedPath.begin(), findedPath.end());
		aStarStart = checkpoint;
	}
	std::vector<Node*> findedPath = astar->findPath(aStarStart, board->endNode);
	path.insert(path.end(), findedPath.begin(), findedPath.end());
	delete astar;
	return path;
}

bool DisplayPath(AStarBoard* board, std::vector<Node*> path,int cellToDisplay)
 {
     if (cellToDisplay < path.size())
     {
         int i=0;
         for(auto node : path)
         {
             CellType type = i<=cellToDisplay?Path:Empty;
             board->SetCellType(node,type,false);
             i++;
         }
     }
     return cellToDisplay == path.size()-1;
 }

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920 / 2, 1080 / 2), "PathFinding");
	window.setFramerateLimit(60);

	sf::Font* font = new sf::Font();
	if (!font->loadFromFile("../../Assets/gamefont.ttf"))
	{
		std::cout<<"Unable to load font.";
	}
	sf::Texture* debugTexture = new sf::Texture();
	if (!debugTexture->loadFromFile("../../Assets/Title.png"))
	{
		std::cout<<"Unable to load texture.";
	}
	
	// Button stuff
	Sprite* title = new Sprite(&window,debugTexture,sf::Vector2f(0.2, 0.1),sf::Vector2f(0.6, 0.6));
	Button* menuButton = new Button(&window, sf::Vector2f(0.4, 0.4), sf::Vector2f(0.2f, 0.07f), sf::Text("Start Game", *font),sf::Color(100,100,100),sf::Color::White);
	std::list<SceneObject*> menuObjects;
	menuObjects.push_back(menuButton);
	menuObjects.push_back(title);
	Scene* menuScene = new Scene(&window, menuObjects);
	Scene* currentScene = menuScene;



	
	Button* startButton = new Button(&window, sf::Vector2f(0, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Find path", *font),sf::Color::Green,sf::Color::White);
	Button* nextButton = new Button(&window, sf::Vector2f(0.5f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Next step", *font),sf::Color::Blue,sf::Color::White);
	Button* previousButton = new Button(&window, sf::Vector2f(0.25f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Previous step", *font),sf::Color::Blue,sf::Color::White);
	Button* restartButton = new Button(&window, sf::Vector2f(0.75f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Restart game", *font),sf::Color::Red,sf::Color::White);
	
	AStarBoard* board = new AStarBoard(&window, sf::Vector2f(0.1f, 0.1f), sf::Vector2i(16, 9), 0.8f);
	std::list<SceneObject*> sceneObjects;

	sceneObjects.push_back(startButton);
	sceneObjects.push_back(nextButton);
	sceneObjects.push_back(previousButton);
	sceneObjects.push_back(restartButton);
	sceneObjects.push_back(board);
	Scene* scene = new Scene(&window, sceneObjects);

	int currentCellToDisplay = 0;
	std::vector<Node*> path;
	bool isPathfindingDone = false;
	bool isFullyDisplayed = false;
	
	SetupProject(board, scene);

	InputSystem* inputSystem = new InputSystem(&window, scene);
	inputSystem->attach("LeftClick", menuButton);
	inputSystem->attach("LeftClick", startButton);
	inputSystem->attach("LeftClick", nextButton);
	inputSystem->attach("LeftClick", previousButton);
	inputSystem->attach("LeftClick", restartButton);
	menuButton->subscribe([&currentScene,scene]()
	{
		currentScene = scene;
	});
	startButton->subscribe([&isPathfindingDone,&board,&path]()
	{
		if (!isPathfindingDone)
		{
			path = CalculatePath(board);
			isPathfindingDone = true;
		}
	});
	previousButton->subscribe([&isPathfindingDone,&board,&path,&isFullyDisplayed,&currentCellToDisplay]()
		{
			if (isPathfindingDone & currentCellToDisplay >0)
			{
				currentCellToDisplay--;
				isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
			}
		});
	nextButton->subscribe([&isPathfindingDone,&board,&path,&isFullyDisplayed,&currentCellToDisplay]()
		{
			if (isPathfindingDone & !isFullyDisplayed)
			{
				isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
				currentCellToDisplay++;
			}
		});
	restartButton->subscribe([&]()
		{
				delete scene;
				board = new AStarBoard(&window, sf::Vector2f(0.1f, 0.1f), sf::Vector2i(16, 9), 0.8f);
				std::list<SceneObject*> sceneObjects;
				sceneObjects.push_back(board);
				scene = new Scene(&window, sceneObjects);

				currentCellToDisplay = 0;
				isPathfindingDone = false;
				isFullyDisplayed = false;
				SetupProject(board, scene);
		});
	//Scene stuff

	bool spacePressed = false;

	while (window.isOpen())
	{
		inputSystem->Update();
		currentScene->Update();
		currentScene->Draw();
	}
	delete scene;
	delete inputSystem;
	delete font;
	delete debugTexture;
	return 0;
}
