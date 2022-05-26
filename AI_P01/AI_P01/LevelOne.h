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

