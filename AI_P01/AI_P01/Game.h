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

