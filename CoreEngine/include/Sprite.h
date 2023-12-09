#pragma once
#include "SceneObject.h"

class Sprite : public SceneObject
{
public:
    Sprite(sf::RenderWindow* renderWindow, sf::Texture* texture, sf::Vector2f position);
    void Start() override;
    void Update() override;
    void Draw() override;
    bool Contains(sf::Vector2i position) override;
    virtual ~Sprite();

private:
    sf::Sprite _sprite;
};