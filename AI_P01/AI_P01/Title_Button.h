#pragma once
#include "Button.h"
class Title_Button : public Button
{
public:
	Title_Button(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	virtual void Update(float _deltatime) override;
};

