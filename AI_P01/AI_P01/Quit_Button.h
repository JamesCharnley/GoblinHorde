#pragma once
#include "Button.h"


//Quit button exits out of the game
class Quit_Button : public Button
{
public:
	Quit_Button(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	virtual void Update(float _deltatime) override;
};

