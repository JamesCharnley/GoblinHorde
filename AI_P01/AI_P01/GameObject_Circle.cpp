#include "Sprite_Component.h"
#include <iostream>
#include "GameObject_Circle.h"


GameObject_Circle::GameObject_Circle(sf::RenderWindow* _window, Scene* _scene)
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

GameObject_Circle::GameObject_Circle()
{
	// initialize and set defaults
	circle = sf::CircleShape(1);
	circle.setOrigin(sf::Vector2f(0.5f, 0.5f));
	objectShape = &circle;
}

void GameObject_Circle::Render()
{
	// render SFML shape
	window->draw(circle);

	GameObject::Render();
}

float GameObject_Circle::GetRadius()
{
	return circle.getRadius();
}

void GameObject_Circle::SetRadius(float _radius)
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




