/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : SinglePlayerModeButton.h
Description : A button that starts the game in single player
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Button.h"
class SinglePlayerModeButton :
    public Button
{
public:
	SinglePlayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	

	virtual void PerformAction() override;
};

