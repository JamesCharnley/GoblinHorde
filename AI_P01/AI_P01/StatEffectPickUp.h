#pragma once
#include "PickUp.h"
class StatEffectPickUp :
    public PickUp
{

public:

    StatEffectPickUp(sf::RenderWindow* _window, Scene* _scene);

protected:

    StatEffectPickUp();

    float effectAmount = 0;
};

