#include "Square.h"

Square::Square(sf::RenderWindow* renderWindows, float diameter,sf::Vector2f position,sf::Color color):
SceneObject(renderWindows,position),_diameter(diameter),_color(color){}

Square::~Square()
{
    delete _shape;
}

void Square::Start()
{
    SceneObject::Start();
    sf::Vector2u windowsSize = _renderWindows->getSize();

    _shape = new sf::RectangleShape(sf::Vector2f(_diameter*windowsSize.x, _diameter * windowsSize.x));
    _shape->setPosition(sf::Vector2f(_position.x*windowsSize.x,_position.y*windowsSize.x));
    _shape->setFillColor(_color);
    
}
void Square::Update()
{
    SceneObject::Update();
    
}
void Square::Draw()
{
    SceneObject::Draw();
    
    _renderWindows->draw(*_shape);
}

void Square::SetColor(sf::Color color)
{
     _shape->setFillColor(color);
}

bool Square::Contains(sf::Vector2i position)
{
    return _shape->getGlobalBounds().contains(position.x, position.y);
}
