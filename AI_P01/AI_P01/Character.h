/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Character.h
Description : Shared implementation for character, base class of Enemy and Player
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectCircle.h"
#include "ITakeDamage.h"


class Character :
    public GameObjectCircle, public ITakeDamage
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Character(sf::RenderWindow* _window, class Scene* _scene);

    // override update
    virtual void Update(float _deltatime) override;

    virtual void Move(sf::Vector2f _movement);

    virtual void TakeDamage(int _amount) override;
    virtual void TakeDamage(int _amount, Character* _player) override;

    void AddHealth(int _amount); //TODO: Move to Player class

    virtual void Destroy() override;

protected:

    float moveSpeed = 100.0f;
    float rotateSpeed = 100.0f;

    int maxHealth = 100;
    int currentHealth = 0;

    sf::Vector2f velocity;

    float targetRotation = 0;

    class Weapon* equippedWeapon = nullptr;
private:

   
};

