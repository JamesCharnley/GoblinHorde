/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GameObjectCircle.h
Description : GameObject with a circle sprite
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObject.h"
class GameObjectCircle :
    public GameObject
{
public:

	// Custom constructor: takes ref to sf::RenderWindow and Scene() class
	GameObjectCircle(sf::RenderWindow* _window, class Scene* _scene);

	// Render override. Called every frame from Scene() class
	virtual void Render() override;

	// return sf::Circle's radius
	float GetRadius();
	// sets sf::Circle's radius
	virtual void SetRadius(float _radius);


protected:
	// private constructor: this class cannot work without the correct parameters that must be passed to custom constructor
	GameObjectCircle();

	// must be assigned to 'objectShape' variable in constructor
	sf::CircleShape circle;
};

