/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : BaseCreator.h
Description : Class to create a base
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "SFML/Graphics.hpp"

class BaseCreator
{
public:

	BaseCreator(sf::RenderWindow* _window, class Scene* _scene);

protected:

	BaseCreator();
};

