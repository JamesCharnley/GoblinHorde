#pragma once
#include "PickUp.h"
class StatEffect_PickUp :
    public PickUp
{

public:

    StatEffect_PickUp(sf::RenderWindow* _window, Scene* _scene);

protected:

    StatEffect_PickUp();

    float effectAmount = 0;
};

