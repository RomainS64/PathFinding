#include "AStarBoardEditor.h"

AStarBoardEditor::AStarBoardEditor(sf::RenderWindow* renderWindows, InputSystem* inputSystem, AStarBoard* AStarBoard,
    sf::Font* font): SceneObject(renderWindows, sf::Vector2f(0,0))
{
    board = AStarBoard;
    _inputSystem = inputSystem;
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
    	
    startButton->Subscribe([this] { StartButtonHandler(); });
    	
    previousButton->Subscribe([this]()
    {
        PreviousButtonHandler();
    });
    nextButton->Subscribe([this]()
    {
        NextButtonhadler();
    });
    restartButton->Subscribe([this]()
    {
        ResetButtonHandler();
    });
    board->Subscribe([this]()
    {
        BoardButtonHandler();
    });
}

AStarBoardEditor::~AStarBoardEditor()
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

std::vector<Node*> AStarBoardEditor::CalculatePath(AStarBoard* board)
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

bool AStarBoardEditor::DisplayPath(AStarBoard* board, std::vector<Node*> path, int cellToDisplay)
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

void AStarBoardEditor::StartButtonHandler()
{
    if (!isPathfindingDone && board->startNode && board->endNode)
    {
        path = CalculatePath(board);
        isPathfindingDone = !path.empty();

    }
    	
}

void AStarBoardEditor::PreviousButtonHandler()
{
    if (isPathfindingDone && currentCellToDisplay > 0)
    {
        currentCellToDisplay--;
        isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
    }
}

void AStarBoardEditor::NextButtonhadler()
{
    if (isPathfindingDone && !isFullyDisplayed)
    {
        isFullyDisplayed = DisplayPath(board, path, currentCellToDisplay);
        currentCellToDisplay++;
    }
}

void AStarBoardEditor::ResetButtonHandler()
{
    currentCellToDisplay = 0;
    DisplayPath(board, path, currentCellToDisplay);
    isPathfindingDone = false;
    isFullyDisplayed = false;
    board->ClearGraph();
}

void AStarBoardEditor::BoardButtonHandler()
{
    
    sf::Vector2i mousePosition = sf::Mouse::getPosition(*_renderWindows) - board->GetBoardPosition();
    
    for (auto cell : board->GetCellsMap())
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
			
}

void AStarBoardEditor::Start()
{
    SceneObject::Start();
    
    startButton->Start();
    nextButton->Start();
    previousButton->Start();
    restartButton->Start();
    wallButton->Start();
    portalButton->Start();
    checkpointButton->Start();
    startCellButton->Start();
    endCellButton->Start();
    emptyButton->Start();

    _inputSystem->Attach("LeftClick", startButton);
    _inputSystem->Attach("LeftClick", nextButton);
    _inputSystem->Attach("LeftClick", previousButton);
    _inputSystem->Attach("LeftClick", restartButton);
    _inputSystem->Attach("LeftClick", wallButton);
    _inputSystem->Attach("LeftClick", portalButton);
    _inputSystem->Attach("LeftClick", checkpointButton);
    _inputSystem->Attach("LeftClick", startCellButton);
    _inputSystem->Attach("LeftClick", endCellButton);
    _inputSystem->Attach("LeftClick", emptyButton);
    _inputSystem->Attach("LeftClick", board);
}

void AStarBoardEditor::Update()
{
    SceneObject::Update();

    startButton->Update();
    nextButton->Update();
    previousButton->Update();
    restartButton->Update();
    wallButton->Update();
    portalButton->Update();
    checkpointButton->Update();
    startCellButton->Update();
    endCellButton->Update();
    emptyButton->Update();
}

void AStarBoardEditor::Draw()
{
    SceneObject::Draw();

    startButton->Draw();
    nextButton->Draw();
    previousButton->Draw();
    restartButton->Draw();
    wallButton->Draw();
    portalButton->Draw();
    checkpointButton->Draw();
    startCellButton->Draw();
    endCellButton->Draw();
    emptyButton->Draw();
}

bool AStarBoardEditor::Contains(sf::Vector2i position)
{
    return false;
}
