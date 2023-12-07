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


void SetupProject(AStarBoard* board,Scene* scene)
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
    board->SetCellType(sf::Vector2i(12,4),Checkpoint);
    board->CreatePortal(sf::Vector2i(1,7),sf::Vector2i(5,8));
    board->ValidateCells();   
}
 std::vector<Node*> CalculatePath(AStarBoard* board)
{
    AStar* astar = new AStar(*board);
    Node* aStarStart = board->startNode;
    std::vector<Node*> path;
    for(auto checkpoint : board->checkpoints)
    {
        std::vector<Node*> findedPath = astar->findPath(aStarStart,checkpoint);
        path.insert(path.end(), findedPath.begin(), findedPath.end());
        aStarStart = checkpoint;
    }
    std::vector<Node*> findedPath = astar->findPath(aStarStart,board->endNode);
    path.insert(path.end(), findedPath.begin(), findedPath.end());
    delete astar;
    return path;
}
bool DisplayPath(AStarBoard* board, std::vector<Node*> path,int cellToDisplay)
 {
     if (cellToDisplay < path.size())
     {
         Node* node = path.at(cellToDisplay);
         board->SetCellType(node,Path,false);
     }
     return cellToDisplay == path.size()-1;
     
 }

int main()
 {
     sf::RenderWindow window(sf::VideoMode(1920/2,1080/2), "PathFinding");
     window.setFramerateLimit(60);

    AStarBoard* board = new AStarBoard(&window,sf::Vector2f(0.1f,0.1f),sf::Vector2i(16,9),0.8);
    std::list<SceneObject*> sceneObjects;
    sceneObjects.push_back(board);
    Scene* scene = new Scene(&window,sceneObjects);

     int currentCellToDisplay = 0;
     std::vector<Node*> path;
     bool isPathfindingDone = false;
     bool isFullyDisplayed = false;
    
    SetupProject(board,scene);
     //Scene stuff

     bool spacePressed = false;
    
     while (window.isOpen())
     {
         sf::Event event;
         while (window.pollEvent(event)) {
             if (event.type == sf::Event::Closed)window.close();
             // Check if the space bar is pressed
             if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Space)spacePressed = false;
             if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space && !spacePressed) {
                 spacePressed = true;
                 if(!isPathfindingDone)
                 {
                     path =  CalculatePath(board);
                     isPathfindingDone = true;
                 }
                 else if(!isFullyDisplayed)
                 {
                     isFullyDisplayed = DisplayPath(board,path,currentCellToDisplay);
                     currentCellToDisplay++;
                 }
                 else
                 {
                     delete scene;
                     board = new AStarBoard(&window,sf::Vector2f(0.1f,0.1f),sf::Vector2i(16,9),0.8);
                     std::list<SceneObject*> sceneObjects;
                     sceneObjects.push_back(board);
                     scene = new Scene(&window,sceneObjects);

                     currentCellToDisplay = 0;
                     isPathfindingDone = false;
                     isFullyDisplayed = false;
                     SetupProject(board,scene);
                 }
             }
         }
         scene->Update();
         scene->Draw();
     }
     delete scene;
     return 0;
 }
