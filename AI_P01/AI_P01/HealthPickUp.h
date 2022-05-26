#pragma once
#include "StatEffectPickUp.h"
class HealthPickUp :
    public StatEffectPickUp
{
public:

    HealthPickUp(sf::RenderWindow* _window, Scene* _scene);

    virtual void Interact(class Player* _player) override;
};

