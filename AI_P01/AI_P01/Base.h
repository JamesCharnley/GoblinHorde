#pragma once
#include "GameObject_Circle.h"
#include "GameObject_Rectangle.h"
#include "ITakeDamage.h"

class Base :
    public GameObject_Circle, public ITakeDamage
{

public:

    Base(sf::RenderWindow* _window, Scene* _scene);
    virtual ~Base() override;
    virtual void Render() override;

    virtual void TakeDamage(int _amount) override;

protected:

    float maxHealth = 1000.0f;
    float currentHealth = 0;

    GameObject_Rectangle* healthBar = nullptr;
};

