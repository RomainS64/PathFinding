#include <iostream>

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

int main() {
    sf::RenderWindow window(sf::VideoMode(1920/2,1080/2), "YOO");
    window.setFramerateLimit(60);

    //Scene stuff
    AStarBoard* board = new AStarBoard(&window,sf::Vector2f(0.1f,0.1f),sf::Vector2i(16,9));
    std::list<SceneObject*> sceneObjects;
    sceneObjects.push_back(board);
    Scene* scene = new Scene(&window,sceneObjects);
    
    scene->Start();
    board->SetCellType(sf::Vector2i(0,0),Start);
    
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
    board->SetCellType(sf::Vector2i(5,7),Wall);
    board->SetCellType(sf::Vector2i(6,7),Wall);
    board->SetCellType(sf::Vector2i(7,7),Wall);
    board->SetCellType(sf::Vector2i(8,7),Wall);
    board->SetCellType(sf::Vector2i(9,7),Wall);
    board->CreatePortal(sf::Vector2i(8,5),sf::Vector2i(5,8));
    board->SetCellType(sf::Vector2i(8,8),End);
    board->ValidateCells();
    
    AStar* astar = new AStar(*board);
    std::vector<Node*> path = astar->findPath(board->startNode,board->endNode);
    std::cout << board->startNode->id<<">>>>>"<< board->endNode->id<<std::endl ;
    if (!path.empty()) {
        std::cout << "Chemin trouvé : ";
        for (Node* node : path) {
            if(node != board->startNode && node != board->endNode)board->SetCellType(node,Path);
            std::cout << node->id << " ";
        }
        std::cout << std::endl;
    }
    else {
        std::cout << "Aucun chemin trouvé." << std::endl;
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)window.close();
        }
        scene->Update();
        scene->Draw();
    }
    delete scene;
}
