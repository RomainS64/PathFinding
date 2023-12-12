#pragma once
#include "AStar.h"
#include "AStarBoard.h"
#include "Button.h"
#include "InputSystem.h"
#include "SceneObject.h"


class AStarBoardEditor : public SceneObject
{
public:
    AStarBoardEditor(sf::RenderWindow* renderWindows,InputSystem* inputSystem,AStarBoard* AStarBoard,sf::Font* font)
        : SceneObject(renderWindows, sf::Vector2f(0,0))
    {
    	board = AStarBoard;
        startButton = new Button(renderWindows, sf::Vector2f(0, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Find path", *font), sf::Color::Green, sf::Color::Black);
        nextButton = new Button(renderWindows, sf::Vector2f(0.5f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Next step", *font), sf::Color::Blue, sf::Color::Black);
        previousButton = new Button(renderWindows, sf::Vector2f(0.25f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Previous step", *font), sf::Color::Blue, sf::Color::Black);
        restartButton = new Button(renderWindows, sf::Vector2f(0.75f, 0), sf::Vector2f(0.2f, 0.07f), sf::Text("Restart game", *font), sf::Color::Red, sf::Color::Black);
        wallButton = new Button(renderWindows, sf::Vector2f(0.f, 0.1f), sf::Vector2f(0.1f, 0.06f), sf::Text("Wall", *font), sf::Color::White, sf::Color::Black);
        portalButton = new Button(renderWindows, sf::Vector2f(0.f, 0.18f), sf::Vector2f(0.1f, 0.06f), sf::Text("Portal", *font), sf::Color::Green, sf::Color::Black);
        checkpointButton = new Button(renderWindows, sf::Vector2f(0.f, 0.26f), sf::Vector2f(0.1f, 0.06f), sf::Text("Checkpoint", *font), sf::Color(255, 128, 0), sf::Color::Black);
        startCellButton = new Button(renderWindows, sf::Vector2f(0.f, 0.34f), sf::Vector2f(0.1f, 0.06f), sf::Text("Start", *font), sf::Color::Blue, sf::Color::Black);
        endCellButton = new Button(renderWindows, sf::Vector2f(0.f, 0.42f), sf::Vector2f(0.1f, 0.06f), sf::Text("End", *font), sf::Color::Red, sf::Color::Black);
        emptyButton = new Button(renderWindows, sf::Vector2f(0.9f, 0.1f), sf::Vector2f(0.1f, 0.06f), sf::Text("Empty", *font), sf::Color(100, 100, 100), sf::Color::Black);

        wallButton->Subscribe([this]() { currentCellType = Wall; });
        portalButton->Subscribe([this]() { currentCellType = Portal; });
        checkpointButton->Subscribe([this]() { currentCellType = Checkpoint; });
        startCellButton->Subscribe([this]() { currentCellType = CellType::Start; });
        endCellButton->Subscribe([this]() { currentCellType = End; });
        emptyButton->Subscribe([this]() { currentCellType = Empty; });

    	
        startButton->Subscribe([this]()
        {
            if (!isPathfindingDone && board->startNode && board->endNode)
            {
                path = CalculatePath(board);
                isPathfindingDone = !path.empty();

            }
        });
        previousButton->Subscribe([this]()
            {
                if (isPathfindingDone && currentCellToDisplay > 0)
                {
                    currentCellToDisplay--;
                    isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
                }
            });
        nextButton->Subscribe([this]()
            {
                if (isPathfindingDone && !isFullyDisplayed)
                {
                    isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
                    currentCellToDisplay++;
                }
            });
        restartButton->Subscribe([this]()
            {
                currentCellToDisplay = 0;
                DisplayPath(board, path, currentCellToDisplay);
                isPathfindingDone = false;
                isFullyDisplayed = false;
                board->ClearGraph();
            });
        board->Subscribe([this,&renderWindows]()
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*renderWindows) - board->GetBoardPosition();
			for (const auto& cell : board->GetCellsMap())
			{
				if (cell.second->square->Contains(mousePosition))
				{
					sf::Vector2i cellPosition = cell.first->position;

					if (currentCellType == CellType::Start || currentCellType == End)
					{
						for (const auto& cell : board->GetCellsMap())
							if (cell.second->cellType == currentCellType)
							{
								board->SetCellType(cell.first, Empty);
								break;
							}
					}
					else if (currentCellType == Portal)
					{
						if (portals.x == sf::Vector2i(-1, -1))
						{
							portals.x = cellPosition;
						}
						else if (portals.y == sf::Vector2i(-1, -1))
						{
							portals.y = cellPosition;
							board->CreatePortal(portals.x, portals.y);
						}
						else
						{
							for (auto portal : board->GetPortals())
							{
								if (portal->entry->position == portals.x)
								{
									board->RemoveEdge(portal->entry, portal->exit);
									break;
								}
								else if (portal->exit->position == portals.x)
								{
									board->RemoveEdge(portal->exit, portal->entry);
									break;
								}
							}
							board->SetCellType(portals.x, Empty);
							board->SetCellType(portals.y, Empty);
							portals.x = cellPosition;
							portals.y = sf::Vector2i(-1, -1);
						}
					}
					else if (currentCellType == Empty && cell.second->cellType == Portal)
					{
						// Remove portal from portal list
						for (auto portal : board->GetPortals())
						{
							if (portal->entry->position == cellPosition)
							{
								board->RemoveEdge(portal->entry, portal->exit);
								break;
							}
							else if (portal->exit->position == cellPosition)
							{
								board->RemoveEdge(portal->exit, portal->entry);
								break;
							}

						}
						board->SetCellType(portals.x, Empty);
						board->SetCellType(portals.y, Empty);
						portals.x = sf::Vector2i(-1, -1);
						portals.y = sf::Vector2i(-1, -1);
					}

					board->SetCellType(cellPosition, currentCellType);
				}
			}
		});

        
        inputSystem->Attach("LeftClick", startButton);
        inputSystem->Attach("LeftClick", nextButton);
        inputSystem->Attach("LeftClick", previousButton);
        inputSystem->Attach("LeftClick", restartButton);
        inputSystem->Attach("LeftClick", wallButton);
        inputSystem->Attach("LeftClick", portalButton);
        inputSystem->Attach("LeftClick", checkpointButton);
        inputSystem->Attach("LeftClick", startCellButton);
        inputSystem->Attach("LeftClick", endCellButton);
        inputSystem->Attach("LeftClick", emptyButton);
        inputSystem->Attach("LeftClick", board);
    }
	~AStarBoardEditor() override
	{
    	delete startButton;
    	delete nextButton;
    	delete previousButton;
    	delete restartButton;
    	delete wallButton;
    	delete portalButton;
    	delete checkpointButton;
    	delete startCellButton;
    	delete endCellButton;
    	delete emptyButton;
    }
    std::vector<Node*> CalculatePath(AStarBoard* board)
    {
        AStar* astar = new AStar(*board);
        Node* aStarStart = board->startNode;
        std::vector<Node*> path;
        board->ValidateCells();
        for (auto checkpoint : board->checkpoints)
        {
            std::vector<Node*> findedPath = astar->findPath(aStarStart, checkpoint);
            if (findedPath.empty())return {};
            path.insert(path.end(), findedPath.begin(), findedPath.end());
            aStarStart = checkpoint;
        }
        std::vector<Node*> findedPath = astar->findPath(aStarStart, board->endNode);
        path.insert(path.end(), findedPath.begin(), findedPath.end());
        delete astar;
        return path;
    }

    bool DisplayPath(AStarBoard* board, std::vector<Node*> path, int cellToDisplay)
    {
        if (cellToDisplay < path.size())
        {
            int i = 0;
            for (auto node : path)
            {
                CellType type = i <= cellToDisplay ? Path : Empty;
                board->SetCellType(node, type, false);
                i++;
            }
        }
        return cellToDisplay == path.size() - 1;
    }
    void Start() override;
    void Update() override;
    void Draw() override;
    bool Contains(sf::Vector2i position) override;

    void SetCellType(CellType type)
    {
        
    }
private:
    AStarBoard* board;
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
