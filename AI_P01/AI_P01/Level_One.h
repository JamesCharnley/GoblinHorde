#pragma once
#include "Scene.h"

class Level_One :
    public Scene
{
public:

	// custom constructor: Takes ref to Game() class and sf::RenderWindow
    Level_One(class Game* _gameClass, sf::RenderWindow* _window);

	// Start override: Create all objects for this scene before starting the update
	virtual void Start() override;

	virtual void Update(float _dtime) override;


private:

	// triggered when player runs out of birds or all pigs are dead
	bool isGameOver = false;



	
};

