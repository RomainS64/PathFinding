﻿#include "AStarBoard.h"

#include <iostream>

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
            Node* node = new Node(x+100*y,sf::Vector2i(x,y));
            BoardCell* cell = new BoardCell;
            cell->cellType = Empty;
            cell->square = square;
            _cells[node] = cell;
            
        }
    }
}

AStarBoard::~AStarBoard()
{
    for(const auto cell : _cells)
    {
        delete cell.second;
    }
    for(const auto portal : _portals)
    {
        delete portal;
    }
}

void AStarBoard::Start()
{
    for(const auto cell : _cells)
    {
         cell.second->square->Start();
        UpdateCell(cell);
    }
    
}

void AStarBoard::Update()
{
    for(const auto cell : _cells)
    {
        cell.second->square->Update();
    }
}

void AStarBoard::Draw()
{
    for(const auto cell : _cells)
    {
        cell.second->square->Draw();
    }
}
void AStarBoard::UpdateCell(std::pair<Node*, BoardCell*> cell)
{
    CellType type = cell.second->cellType;
    switch(type) {
    case Empty:
        cell.second->square->SetColor(sf::Color(100,100,100));
        break;
    case Wall:
        cell.second->square->SetColor(sf::Color::White);
        break;
    case Portal:
        cell.second->square->SetColor(sf::Color::Green);
        break;
    case Path:
        cell.second->square->SetColor(sf::Color::Yellow);
        break;
    case CellType::Start:
        cell.second->square->SetColor(sf::Color::Blue);
        startNode = cell.first;
        break;
    case End:
        cell.second->square->SetColor(sf::Color::Red);
        endNode = cell.first;
        break;
    default:
        ;
    }
}
void AStarBoard::SetCellType(sf::Vector2i position, CellType type)
{
    std::pair<Node*, BoardCell*> cell = GetCell(position);
    cell.second->cellType = type;
    UpdateCell(cell);
    
}

void AStarBoard::CreatePortal(sf::Vector2i entry, sf::Vector2i exit)
{
    auto entryCell =GetCell(entry);
    auto exitCell = GetCell(exit);
    Portals* portals = new Portals(entryCell.first,exitCell.first);
    entryCell.second->cellType = Portal;
    exitCell.second->cellType= Portal;
    UpdateCell(entryCell);
    UpdateCell(exitCell);
    _portals.push_back(portals);
}

void AStarBoard::SetCellType(Node* node, CellType type)
{
    _cells[node]->cellType = type;
    UpdateCell(*_cells.find(node));
}

std::pair<Node*, BoardCell*> AStarBoard::GetCell(sf::Vector2i position)
{
    for(auto cell : _cells)
    {
        if(cell.first->position == position)
        {
            return cell;
        }
    }
    std::cout<< "No cell founded at position"<<position.x<<";"<<position.y<<std::endl;
    return *_cells.begin();
}

void AStarBoard::ValidateCells()
{
    for(auto cell : _cells)
    {
        addNode(cell.first);
    }
    for(auto portal : _portals)
    {
        addEdge(portal->entry,portal->exit);
    }
    for (int x = 0; x < _size.x; x++) {
        for (int y = 0; y < _size.y; y++) {
            std::pair<Node*, BoardCell*> cell = GetCell(sf::Vector2i(x,y));
            if(cell.second->cellType == Wall)continue;
            if (x !=0) {
                
                std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x-1,y));
                if(linkedCell.second->cellType != Wall)
                {
                    addEdge(cell.first,linkedCell.first);
                }
                
            }
            if (x != _size.x-1) {
                std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x+1,y));
                if(linkedCell.second->cellType != Wall)
                {
                    std::cout<<"link to the right"<< cell.first->id << ">"<< linkedCell.first->id<< std::endl;
                    addEdge(cell.first,linkedCell.first);
                }
                
            }
            if (y != 0) {
                std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x,y-1));
                if(linkedCell.second->cellType != Wall)
                {
                    addEdge(cell.first,linkedCell.first);
                }
                
            }
            if (y != _size.y-1) {
                std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x,y+1));
                if(linkedCell.second->cellType != Wall)
                {
                    addEdge(cell.first,linkedCell.first);
                }
                
            }
        }
    }
}

bool AStarBoard::Contains(sf::Vector2i position)
{
    return _rect.contains(position.x,position.y);
}
