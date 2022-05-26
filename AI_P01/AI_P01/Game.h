/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Game.h
Description : Main game loop, holds all scenes to be used in the game
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Game
{

public:

	Game();
	virtual ~Game();

	//called from constructor, used for any setup that can't be done in constructor
	virtual void Start();

	// call to change to a new scene. Code must be added to the function to tell it what Scene.h class should be loaded with the string
	void ChangeScene(std::string _name);

	void Exit();

protected:

	// Create SFML RenderWindow. Size of window should not be set directly in the function. Set size in Utility.h
	virtual void CreateGameWindow();

	//If NewScene is set to true, this function will be called at the end of the current while loop
	//and open a new scene class
	virtual void LoadScene(std::string _sceneName) = 0;

	bool newScene = false;

	std::string gameName;

	class Scene* currentScene;

	std::string defaultStartScene;

	std::string nextScene;

	sf::RenderWindow* window;

};

