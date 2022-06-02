/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : QuitButton.h
Description : A button that quits the game
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Button.h"

//Quit button exits out of the game
class QuitButton : public Button
{
public:
	QuitButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	virtual void PerformAction() override;
};

