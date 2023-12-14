#include "AStarBoard.h"

#include <iostream>

AStarBoard::AStarBoard(sf::RenderWindow* renderWindows, sf::Vector2f position, sf::Vector2i size, float boardWidth) :
	SceneObject(renderWindows, position), _size(size)
{
	sf::Vector2u windowsSize = _renderWindows->getSize();
	_rect.setPosition(_position.x * windowsSize.x, _position.y * windowsSize.x);
	_rect.setSize(sf::Vector2f(boardWidth * windowsSize.x, boardWidth * windowsSize.y));

	_spaceBetweenSquare = boardWidth / (float)size.x;
	for (int x = 0; x < size.x; x++)
	{
		for (int y = 0; y < size.y; y++)
		{
			Square* square = new Square(
				renderWindows, _spaceBetweenSquare * 0.9f,
				sf::Vector2f(_position.x + (x * _spaceBetweenSquare), _position.y + (y * _spaceBetweenSquare)),
				sf::Color::White);
			Node* node = new Node(x + 100 * y, sf::Vector2i(x, y));
			BoardCell* cell = new BoardCell;
			cell->cellType = Empty;
			cell->square = square;
			_cells[node] = cell;

		}
	}
}

AStarBoard::~AStarBoard()
{
	for (const auto cell : _cells)
	{
		delete cell.second;
	}
	for (const auto portal : _portals)
	{
		delete portal;
	}
}

void AStarBoard::Start()
{
	for (const auto cell : _cells)
	{
		cell.second->square->Start();
		UpdateCell(cell);
	}

}

void AStarBoard::Update()
{
	for (const auto cell : _cells)
	{
		cell.second->square->Update();
	}
}

void AStarBoard::Draw()
{
	for (const auto cell : _cells)
	{
		cell.second->square->Draw();
	}
}

void AStarBoard::ClearGraph()
{
	Graph::ClearGraph();
	for (auto cell : _cells)
	{
		SetCellType(cell.first->position, Empty);
	}
	checkpoints.clear();
	_portals.clear();
	startNode = nullptr;
	endNode = nullptr;
	
}

void AStarBoard::UpdateCell(std::pair<Node*, BoardCell*> cell)
{
	CellType type = cell.second->cellType;
	switch (type) {
	case Empty:
		cell.second->square->SetColor(sf::Color(100, 100, 100));
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
	case Checkpoint:
		cell.second->square->SetColor(sf::Color(255, 128, 0));
		checkpoints.push_back(cell.first);
		break;
	default:
		;
	}
}
void AStarBoard::OnNotify(const EventBase& _eventB)
{
	if (_eventB._id == "LeftClick")
	{
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*_renderWindows);
		if (Contains(mousePosition))
		{
			for (const auto& callback : _callbacks)
			{
				callback();
			}
		}
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
	auto entryCell = GetCell(entry);
	auto exitCell = GetCell(exit);
	Portals* portals = new Portals(entryCell.first, exitCell.first);
	entryCell.second->cellType = Portal;
	exitCell.second->cellType = Portal;
	UpdateCell(entryCell);
	UpdateCell(exitCell);
	_portals.push_back(portals);
}

void AStarBoard::SetCellType(Node* node, CellType type, bool overrideCell)
{
	if (overrideCell || _cells[node]->cellType == Empty || _cells[node]->cellType == Path)
	{
		_cells[node]->cellType = type;
		UpdateCell(*_cells.find(node));
	}

}

std::pair<Node*, BoardCell*> AStarBoard::GetCell(sf::Vector2i position)
{
	for (auto cell : _cells)
	{
		if (cell.first->position == position)
		{
			return cell;
		}
	}
	std::cout << "No cell founded at position" << position.x << ";" << position.y << std::endl;
	return *_cells.begin();
}

void AStarBoard::ValidateCells()
{
	for (auto cell : _cells)
	{
		AddNode(cell.first);
	}
	for (auto portal : _portals)
	{
		AddEdge(portal->entry, portal->exit);
	}
	for (int x = 0; x < _size.x; x++) {
		for (int y = 0; y < _size.y; y++) {
			std::pair<Node*, BoardCell*> cell = GetCell(sf::Vector2i(x, y));
			if (cell.second->cellType == Wall || cell.second->cellType == End)continue;
			if (x != 0) {

				std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x - 1, y));
				if (linkedCell.second->cellType != Wall)
				{
					AddEdge(cell.first, linkedCell.first);
				}

			}
			if (x != _size.x - 1) {
				std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x + 1, y));
				if (linkedCell.second->cellType != Wall)
				{
					AddEdge(cell.first, linkedCell.first);
				}

			}
			if (y != 0) {
				std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x, y - 1));
				if (linkedCell.second->cellType != Wall)
				{
					AddEdge(cell.first, linkedCell.first);
				}
			}
			if (y != _size.y - 1) {
				std::pair<Node*, BoardCell*> linkedCell = GetCell(sf::Vector2i(x, y + 1));
				if (linkedCell.second->cellType != Wall)
				{
					AddEdge(cell.first, linkedCell.first);
				}
			}
		}
	}
}

std::map<Node*, BoardCell*> AStarBoard::GetCellsMap()
{
	return _cells;
}

std::list<Portals*> AStarBoard::GetPortals()
{
	return _portals;
}

sf::Vector2i AStarBoard::GetBoardPosition()
{
	return _renderWindows->mapCoordsToPixel(_position);
}

bool AStarBoard::Contains(sf::Vector2i position)
{
	sf::Vector2f relativePosition = _renderWindows->mapPixelToCoords(position);
	return _rect.getGlobalBounds().contains(sf::Vector2f(relativePosition));
}
