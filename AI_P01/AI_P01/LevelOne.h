/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : LevelOne.h
Description : The first scene of the game
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Scene.h"
#include <SFML/Audio.hpp>

class LevelOne :
    public Scene
{
public:

	// custom constructor: Takes ref to Game() class and sf::RenderWindow
    LevelOne(class Game* _gameClass, sf::RenderWindow* _window, int _numberOfPlayers);

	// Start override: Create all objects for this scene before starting the update
	virtual void Start() override;

	virtual void Update(float _dtime) override;

	

private:

	
	
	// triggered when player runs out of birds or all pigs are dead
	bool isGameOver = false;
	sf::Music music;
	int numberOfPlayers = 1;

	
};

