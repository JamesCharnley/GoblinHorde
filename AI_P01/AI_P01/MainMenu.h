#pragma once

#include "Scene.h"

class MainMenu :
	public Scene
{
public:
	MainMenu(class Game* _gameClass, sf::RenderWindow* window);

	virtual void Start() override;
};

