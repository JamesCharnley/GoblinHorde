/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
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
    Base(sf::RenderWindow* _window, Scene* _scene, int _playerCount, float _repairTime);
    virtual ~Base() override;
    virtual void Render() override;

    // TakeDamage interface overrides
    virtual void TakeDamage(int _amount) override;
    virtual void TakeDamage(int _amount, Character* _player) override;

    bool InRange(class Player* _player);

    void Repair(float _deltaTime);

    float GetCurrentHealth() { return currentHealth; };
    float GetMaxHealth() { return maxHealth; };


protected:    
    const int PLAYER_COUNT = 1;
    const float REPAIR_TIME = 10.0f;
    float maxHealth = 1000.0f;
    float currentHealth = 0;

    GameObjectRectangle* healthBar = nullptr;
};

