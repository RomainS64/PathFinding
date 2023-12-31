﻿#include "Sprite.h"

Sprite::Sprite(sf::RenderWindow* renderWindow, sf::Texture* texture, sf::Vector2f position,sf::Vector2f size)
    : SceneObject(renderWindow, position)
{
    _sprite = new sf::Sprite(*texture);
    _sprite->setScale(size);
    _sprite->setPosition(_position.x * renderWindow->getSize().x, _position.y * renderWindow->getSize().y);
}

void Sprite::Start(){}

void Sprite::Update(){}

void Sprite::Draw()
{
    _renderWindows->draw(*_sprite);
}

bool Sprite::Contains(sf::Vector2i position)
{
    return _sprite->getGlobalBounds().contains(static_cast<sf::Vector2f>(position));
}

Sprite::~Sprite()
{
    delete _sprite;
}