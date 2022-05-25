#pragma once
#include "Button.h"
class BackButton :
    public Button
{
public:

    BackButton(sf::RenderWindow* _window, Scene* _scene, sf::Vector2f _position);
    virtual void Update(float _deltatime) override;
};

