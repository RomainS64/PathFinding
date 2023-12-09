#pragma once
#include <iostream>
#include "SceneObject.h"
#include "Event.h"

class Button : public SceneObject, public EventSubscriber
{
public:
	Button(sf::RenderWindow* renderWindows, sf::Vector2f position, sf::Vector2f size, sf::Text text);
	~Button();

	virtual void Start() override;
	virtual void Update() override;
	virtual void Draw() override;
	virtual bool Contains(sf::Vector2i position) override;

	virtual void onNotify(const EventBase& _eventB) override;

	void SetButtonColor(sf::Color color);
	void SetTextColor(sf::Color color);
	void SetButtonOutlineColor(sf::Color color);
	void SetButtonOutlineThickness(float thickness);

private:
	sf::RectangleShape _button;
	sf::Text _text;
	sf::Vector2f _size;
};

