#pragma once
#include "SceneObject.h"
#include "Square.h"
#include "Graph.h"


enum CellType
{
    Empty,Wall,Portal,Path,Start,End
};
struct BoardCell
{
    ~BoardCell()
    {
        delete square;
    }
    CellType cellType;
    Square* square;
   
};
struct Portals
{
    Portals( BoardCell* first,BoardCell* second):entry(first),exit(second){}
    BoardCell* entry;
    BoardCell* exit;
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
    void CreatePortal(sf::Vector2i entry,sf::Vector2i exit);
    void SetCellType(Node*,CellType type);
    std::pair<Node*,BoardCell*> GetCell(sf::Vector2i position);
    void ValidateCells();
    bool Contains(sf::Vector2i position) override;

    void UpdateCell(std::pair<Node*, BoardCell*> cell);
    
    Node* startNode;
    Node* endNode;
    
private:
    std::list<Portals*> _portals;
    std::map<Node*,BoardCell*> _cells;
    
    sf::Vector2i _size;
    sf::IntRect _rect;
};
