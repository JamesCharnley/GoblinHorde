#pragma once
#include "StatEffect_PickUp.h"
class Health_PickUp :
    public StatEffect_PickUp
{
public:

    Health_PickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual void Interact(class Player* _player) override;
};

