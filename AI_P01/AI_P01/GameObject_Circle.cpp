#include "Sprite_Component.h"
#include <iostream>
#include "GameObjectCircle.h"


GameObjectCircle::GameObjectCircle(sf::RenderWindow* _window, Scene* _scene)
{
	// create sf::CircleShape with default radius of 1
	circle = sf::CircleShape(1);

	// set SFML shape's origin to center
	circle.setOrigin(sf::Vector2f(0.5f, 0.5f));

	// assign ref to circle to objectShape
	objectShape = &circle;

	// assign ref to sf::RenderWindow
	window = _window;

	// assign ref to Scene() class
	scene = _scene;
}

GameObjectCircle::GameObjectCircle()
{
	// initialize and set defaults
	circle = sf::CircleShape(1);
	circle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &circle;
}

void GameObjectCircle::Render()
{
	// render SFML shape
	window->draw(circle);

	GameObject::Render();
}

float GameObjectCircle::GetRadius()
{
	return circle.getRadius();
}

void GameObjectCircle::SetRadius(float _radius)
{
	circle.setRadius(_radius);

	// update the origin to center of circle after radius change
	circle.setOrigin(sf::Vector2f(_radius, _radius));

	// update scale of sprite to match shape
	if (sprite != nullptr)
	{
		sprite->UpdateSize(sf::Vector2f(_radius * 2, _radius * 2));
	}
}




