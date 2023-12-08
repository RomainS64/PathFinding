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

	virtual void onNotify(const EventID& _ID) override;

private:
	sf::RectangleShape _button;
	sf::Text _text;
	sf::Font _font;
	sf::Vector2f _size;
};

