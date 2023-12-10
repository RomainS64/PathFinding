#include "Button.h"
#include "InputSystem.h"

Button::Button(sf::RenderWindow* renderWindows, sf::Vector2f position, sf::Vector2f size, sf::Text text,sf::Color buttonColor,sf::Color textColor) : SceneObject(renderWindows, position), _size(size), _text(text)
{
	sf::Vector2u windowsSize = _renderWindows->getSize();
	
	_button = sf::RectangleShape(sf::Vector2f(size.x*windowsSize.x,size.y*windowsSize.x));
	_button.setPosition(sf::Vector2f(_position.x*windowsSize.x,_position.y*windowsSize.x));
	_button.setFillColor(buttonColor);
	_button.setOutlineColor(buttonColor);
	_button.setOutlineThickness(1.f);

	_text.setPosition(_position.x*windowsSize.x+10, _position.y*windowsSize.x+((size.y*windowsSize.x)/4.f));
	_text.setCharacterSize(25);
	_text.setFillColor(textColor);
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
