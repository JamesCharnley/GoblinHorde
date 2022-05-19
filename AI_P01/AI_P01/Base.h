#pragma once
#include "GameObject_Circle.h"
#include "GameObject_Rectangle.h"
#include "ITakeDamage.h"

class Base :
    public GameObject_Circle, public ITakeDamage
{

public:

    // custom constructor. Parameters: sf::RenderWindow*, Scene*
    Base(sf::RenderWindow* _window, Scene* _scene);
    virtual ~Base() override;
    virtual void Render() override;

    // TakeDamage interface overrides
    virtual void TakeDamage(int _amount) override;
    virtual void TakeDamage(int _amount, Character* _player) override;

    bool InRange(class Player* _player);

    void Repair(float _repairAmount);

protected:

    

    float maxHealth = 1000.0f;
    float currentHealth = 0;

    GameObject_Rectangle* healthBar = nullptr;
};

