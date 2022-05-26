/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Base.h
Description : A base with health theat can be attacked by Enemies
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectCircle.h"
#include "GameObjectRectangle.h"
#include "ITakeDamage.h"

class Base :
    public GameObjectCircle, public ITakeDamage
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

    float GetCurrentHealth() { return currentHealth; };
    float GetMaxHealth() { return maxHealth; };

protected:

    

    float maxHealth = 1000.0f;
    float currentHealth = 0;

    GameObjectRectangle* healthBar = nullptr;
};

