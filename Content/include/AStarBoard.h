#pragma once
#include "SceneObject.h"
#include "Square.h"
#include "Graph.h"


enum CellType
{
    Empty,Wall,Portal,Start,End
};
struct BoardCell
{
    CellType cellType;
    sf::Vector2i positionInBoard;
    Square* square;
};
class AStarBoard : public Graph,public SceneObject
{
public:
    AStarBoard(sf::RenderWindow* renderWindows,sf::Vector2f position,sf::Vector2i size);
    ~AStarBoard() override;
    void Start()override;
    void Update()override;
    void Draw()override;
    void SetCellType(sf::Vector2i position,CellType type);
    std::pair<Node*,BoardCell> GetCell(sf::Vector2i position);
    void ValidateCells();
    bool Contains(sf::Vector2i position) override;
    
    Node* startNode;
    Node* endNode;
private:
    std::map<Node*,BoardCell> _cells;
    sf::Vector2i _size;
    sf::IntRect _rect;
};
