#pragma once
#include "SceneObject.h"

class Square : public SceneObject
{
public:
    Square(sf::RenderWindow* renderWindows,float diameter,sf::Vector2f position,sf::Color color);
    ~Square() override;
    void Start()override;
    void Update()override;
    void Draw()override;
    void SetColor(sf::Color color);
    bool Contains(sf::Vector2i position) override;

private:
    sf::RectangleShape* _shape;
    float _diameter;
    sf::Color _color;
    
    
};
