#include "Button.h"
#include "InputSystem.h"

Button::Button(sf::RenderWindow* renderWindows, sf::Vector2f position, sf::Vector2f size, sf::Text text) : SceneObject(renderWindows, position), _size(size), _text(text)
{
	_button = sf::RectangleShape(_size);
	_button.setPosition(_position);
	_button.setFillColor(sf::Color::White);
	_button.setOutlineColor(sf::Color::Black);
	_button.setOutlineThickness(1.f);

	_text.setPosition(_position.x + 10.0f, _position.y + 5.0f);
	_text.setCharacterSize(20);
	_text.setFillColor(sf::Color::Black);
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

}

void Button::Draw()
{
	_renderWindows->draw(_button);
	_renderWindows->draw(_text);
}

bool Button::Contains(sf::Vector2i position)
{
	sf::Vector2f _position = _renderWindows->mapPixelToCoords(position);
	if (_button.getGlobalBounds().contains(_position))
	{
		return true;
	}
	return false;
}

void Button::onNotify(const EventBase& _eventB)
{
	EventID id = _eventB._id;
	if (id == "LeftClick")
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

void Button::SetButtonColor(sf::Color color)
{
	_button.setFillColor(color);
}

void Button::SetTextColor(sf::Color color)
{
	_text.setFillColor(color);
}

void Button::SetButtonOutlineColor(sf::Color color)
{
	_button.setOutlineColor(color);
}

void Button::SetButtonOutlineThickness(float thickness)
{
	_button.setOutlineThickness(thickness);
}
