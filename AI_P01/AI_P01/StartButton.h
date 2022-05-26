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

