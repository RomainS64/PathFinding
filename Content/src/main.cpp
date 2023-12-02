#include <iostream>

#include "imgui.h"
#include "imgui-SFML.h"

#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

#include "Scene.h"
#include "Square.h"
#include "../../Build/App/AStarBoard.h"
#include "AStar

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
    board->SetCellType(sf::Vector2i(15,8),End);

    board->ValidateCells();
    AStar* astar = new AStar(*board);
    std::vector<Node*> path = astar->findPath(board->startNode,board->endNode);
    if (!path.empty()) {
        std::cout << "Chemin trouvé : ";
        for (Node* node : path) {
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
