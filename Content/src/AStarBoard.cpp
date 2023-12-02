#include "AStarBoard.h"

AStarBoard::AStarBoard(sf::RenderWindow* renderWindows,sf::Vector2f position,sf::Vector2i size):
SceneObject(renderWindows,position),_size(size)
{
    sf::Vector2u windowsSize = _renderWindows->getSize();
    _rect.left = _position.x * windowsSize.x;
    _rect.top = _position.y * windowsSize.x;
    _rect.width = size.x*0.05f;
    _rect.height= size.y*0.05f;
    
    for(int x=0;x<size.x;x++)
    {
        for(int y=0;y<size.y;y++)
        {
            Square* square = new Square(
                renderWindows,0.04f,
                sf::Vector2f(_position.x+(x*0.05f),_position.y+(y*0.05f)),
                sf::Color::White);
            Node* node = new Node(x+10*y);
            BoardCell cell;
            cell.cellType = Empty;
            cell.square = square;
            cell.positionInBoard = sf::Vector2i(x,y);
            _cells[node] = cell;
        }
    }
}

AStarBoard::~AStarBoard()
{
    for(const auto cell : _cells)
    {
        delete cell.second.square;
    }
}

void AStarBoard::Start()
{
    for(const auto cell : _cells)
    {
         cell.second.square->Start();
    }
}

void AStarBoard::Update()
{
    for(const auto cell : _cells)
    {
        cell.second.square->Update();
    }
}

void AStarBoard::Draw()
{
    for(const auto cell : _cells)
    {
        cell.second.square->Draw();
    }
}

void AStarBoard::SetCellType(sf::Vector2i position, CellType type)
{
    std::pair<Node*, BoardCell> cell = GetCell(position);
    cell.second.cellType = type;
    switch(type) {
    case Empty:
        cell.second.square->SetColor(sf::Color(100,100,100));
        break;
    case Wall:
        cell.second.square->SetColor(sf::Color::White);
        break;
    case Portal:
        cell.second.square->SetColor(sf::Color::Green);
        break;
    case CellType::Start:
        cell.second.square->SetColor(sf::Color::Blue);
        startNode = cell.first;
        break;
    case End:
        cell.second.square->SetColor(sf::Color::Red);
        endNode = cell.first;
        break;
    default:
        ;
    }
}

std::pair<Node*, BoardCell> AStarBoard::GetCell(sf::Vector2i position)
{
    for(auto cell : _cells)
    {
        if(cell.second.positionInBoard == position)
        {
            return cell;
        }
    }
    return  std::pair<Node*, BoardCell>(_cells.begin()->first,_cells.begin()->second);
}

void AStarBoard::ValidateCells()
{
    for(auto cell : _cells)
    {
        addNode(cell.first);
    }
    for (int x = 0; x < _size.x; x++) {
        for (int y = 0; y < _size.y; y++) {
            std::pair<Node*, BoardCell> cell = GetCell(sf::Vector2i(x,y));
            if(cell.second.cellType == Wall)return;
            int id = x + (10 * y);
            if (x !=0) {
                std::pair<Node*, BoardCell> linkedCell = GetCell(sf::Vector2i(x-1,y));
                addEdge(cell.first,linkedCell.first);
            }
            if (x != _size.x-1) {
                std::pair<Node*, BoardCell> linkedCell = GetCell(sf::Vector2i(x+1,y));
                addEdge(cell.first,linkedCell.first);
            }
            if (y != 0) {
                std::pair<Node*, BoardCell> linkedCell = GetCell(sf::Vector2i(x,y-1));
                addEdge(cell.first,linkedCell.first);
            }
            if (y != _size.y-1) {
                std::pair<Node*, BoardCell> linkedCell = GetCell(sf::Vector2i(x,y+1));
                addEdge(cell.first,linkedCell.first);
            }
        }
    }
}

bool AStarBoard::Contains(sf::Vector2i position)
{
    return _rect.contains(position.x,position.y);
}
