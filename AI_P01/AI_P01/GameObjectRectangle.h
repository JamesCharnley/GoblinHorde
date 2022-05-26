/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GameObjectRectangle.h
Description : GameObject with a rectangle sprite
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObject.h"
class GameObjectRectangle :
    public GameObject
{

public:

    // custom constructor for a rectangle shape. Takes ref to sf::RenderWindow and ref to Scene() class
    GameObjectRectangle(sf::RenderWindow* _window, class Scene* _scene);

    // Render() override. called every frame from Scene() class
    virtual void Render() override;

    // return size of SFML shape
	sf::Vector2f GetSize();
    // set size of SFML shape
	void SetSize(sf::Vector2f _size);


protected:

    // private constructor: Class cannot work without the correct parameters passed to the custom constructor
    GameObjectRectangle();

    // Must be assigned to 'objectShape' variable in constructor
    sf::RectangleShape rectangle;
};

