#pragma once
#include "Button.h"
class SinglePlayerModeButton :
    public Button
{
public:
	SinglePlayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
	virtual void Update(float _deltatime) override;
};

