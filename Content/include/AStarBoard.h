#pragma once
#include "SceneObject.h"
#include "Square.h"
#include "Graph.h"
#include "Event.h"


enum CellType
{
    Empty,Wall,Portal,Path,Start,Checkpoint,End
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
    Portals( Node* first,Node* second):entry(first),exit(second){}
    Node* entry;
    Node* exit;
};
class AStarBoard : public Graph,public SceneObject, public EventSubscriber
{
public:
    AStarBoard(sf::RenderWindow* renderWindows,sf::Vector2f position,sf::Vector2i size,float boardWidth);
    ~AStarBoard() override;
    void Start()override;
    void Update()override;
    void Draw()override;
    void SetCellType(sf::Vector2i position,CellType type);
    void CreatePortal(sf::Vector2i entry,sf::Vector2i exit);
    void SetCellType(Node*,CellType type,bool overrideCell = true);
    std::pair<Node*,BoardCell*> GetCell(sf::Vector2i position);
    void ValidateCells();
    std::map<Node*,BoardCell*> GetCellsMap();
    sf::Vector2i GetBoardPosition();
    bool Contains(sf::Vector2i position) override;

    void UpdateCell(std::pair<Node*, BoardCell*> cell);

    virtual void OnNotify(const EventBase& _eventB) override;
    
    Node* startNode;
    Node* endNode;
    std::list<Node*> checkpoints;
private:
    
    std::list<Portals*> _portals;
    std::map<Node*,BoardCell*> _cells;
    
    sf::Vector2i _size;
    sf::RectangleShape _rect;
    float _spaceBetweenSquare;
};
