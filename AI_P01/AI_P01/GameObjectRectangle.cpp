#include <iostream>
#include "SpriteComponent.h"
#include "GameObjectRectangle.h"

GameObjectRectangle::GameObjectRectangle()
{
	// initialize and set defaults
	rectangle = sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &rectangle;
}

GameObjectRectangle::GameObjectRectangle(sf::RenderWindow* _window, Scene* _scene)
{
	// initialize and set defaults. 
	rectangle = sf::RectangleShape(sf::Vector2f(1, 1));
	rectangle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &rectangle;

	// set refs to sf::RenderWindow and Scene() class
	window = _window;
	scene = _scene;
}

void GameObjectRectangle::Render()
{
	// render SFML shape
	window->draw(rectangle);

	GameObject::Render();
}

sf::Vector2f GameObjectRectangle::GetSize()
{
	return rectangle.getSize();
}

void GameObjectRectangle::SetSize(sf::Vector2f _size)
{
	rectangle.setSize(_size);
	rectangle.setOrigin(sf::Vector2f(_size.x / 2, _size.y / 2));

	// update scale of sprite to match shape
	if (sprite != nullptr)
	{
		sprite->UpdateSize(_size);
	}
}

