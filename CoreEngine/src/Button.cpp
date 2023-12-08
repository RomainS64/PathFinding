#include "Button.h"

Button::Button(sf::RenderWindow* renderWindows, sf::Vector2f position, sf::Vector2f size, sf::Text text) : SceneObject(renderWindows, position), _size(size), _text(text)
{
}

Button::~Button()
{
	// TODO: Implement ~Button
}

void Button::Start()
{
	// TODO: Implement Start
}

void Button::Update()
{
	// TODO: Implement Update
}

void Button::Draw()
{
	// TODO: Implement Draw
}

bool Button::Contains(sf::Vector2i position)
{
	return false;
}

void Button::onNotify(const EventID& _ID)
{
	// TODO: Implement onNotify
}
