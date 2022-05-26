/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : StartButton.h
Description : A button that starts the game
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Button.h"

class StartButton : public Button
{
public:
	StartButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position, int _numOfPlayers);
	virtual void Update(float _deltatime) override;

private:

	int numberOfPlayers = 1;
};

