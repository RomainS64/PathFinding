#pragma once
#include "AStar.h"
#include "AStarBoard.h"
#include "Button.h"
#include "InputSystem.h"
#include "SceneObject.h"


class AStarBoardEditor : public SceneObject
{
public:
    AStarBoardEditor(sf::RenderWindow* renderWindows,InputSystem* inputSystem,AStarBoard* AStarBoard,sf::Font* font);
	~AStarBoardEditor() override;
    std::vector<Node*> CalculatePath(AStarBoard* board);
    bool DisplayPath(AStarBoard* board, std::vector<Node*> path, int cellToDisplay);
    void StartButtonHandler();
	void PreviousButtonHandler();
    void NextButtonhadler();
    void ResetButtonHandler();
    void BoardButtonHandler();
    void Start() override;
    void Update() override;
    void Draw() override;
    bool Contains(sf::Vector2i position) override;
private:
    AStarBoard* board;
    InputSystem* _inputSystem;
    
    CellType currentCellType = Empty;
    int currentCellToDisplay = 0;
    bool isPathfindingDone = false;
    bool isFullyDisplayed = false;
    std::vector<Node*> path;
	sf::Vector2<sf::Vector2i> portals = sf::Vector2<sf::Vector2i>(sf::Vector2i(-1, -1), sf::Vector2i(-1, -1));

    Button* startButton;
    Button* nextButton;
    Button* previousButton;
    Button* restartButton;
    Button* wallButton;
    Button* portalButton;
    Button* checkpointButton;
    Button* startCellButton;
    Button* endCellButton;
    Button* emptyButton;
};
