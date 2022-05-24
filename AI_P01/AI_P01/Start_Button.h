#pragma once
#include "Button.h"

class Start_Button : public Button
{
public:
	Start_Button(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	virtual void Update(float _deltatime) override;
};

