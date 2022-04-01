#include "GameObject_Rectangle.h"
#include <iostream>
GameObject_Rectangle::GameObject_Rectangle()
{
	// initialize and set defaults
	rectangle = sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &rectangle;
}

GameObject_Rectangle::GameObject_Rectangle(sf::RenderWindow* _window, Scene* _scene)
{
	// initialize and set defaults. 
	rectangle = sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &rectangle;

	// set refs to sf::RenderWindow and Scene() class
	window = _window;
	scene = _scene;
}

void GameObject_Rectangle::Render()
{
	// render SFML shape
	window->draw(rectangle);
}

sf::Vector2f GameObject_Rectangle::GetSize()
{
	return rectangle.getSize();
}

void GameObject_Rectangle::SetSize(sf::Vector2f _size)
{
	rectangle.setSize(_size);
	rectangle.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));
}

