#pragma once
#include "Button.h"
class MultiplayerModeButton :
    public Button
{
public:
    MultiplayerModeButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
    virtual void Update(float _deltatime) override;
};

