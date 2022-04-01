#pragma once
#include "GameObject.h"
class GameObject_Circle :
    public GameObject
{
public:

	// Custom constructor: takes ref to sf::RenderWindow and Scene() class
	GameObject_Circle(sf::RenderWindow* _window, class Scene* _scene);

	// Render override. Called every frame from Scene() class
	virtual void Render() override;

	// return sf::Circle's radius
	float GetRadius();
	// sets sf::Circle's radius
	virtual void SetRadius(float _radius);


protected:
	// private constructor: this class cannot work without the correct parameters that must be passed to custom constructor
	GameObject_Circle();

	// must be assigned to 'objectShape' variable in constructor
	sf::CircleShape circle;
};

