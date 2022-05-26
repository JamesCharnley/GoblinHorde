/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Enemy.h
Description : Enemy to attack the player and base
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Character.h"
class Enemy :
    public Character
{
public:

    Enemy(sf::RenderWindow* _window, Scene* _scene, class Base* _base);
    Enemy(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base);

    virtual void Update(float _deltatime) override;

    void AddPlayer(class Player* _player);

    virtual void TakeDamage(int _amount, Character* _player) override;

    virtual void Destroy() override;

protected:

    std::vector<class Player*> players;
    class Player* closestPlayer = nullptr;
    class EnemySpawner* spawner = nullptr;

    int goldReward = 100;

    class Base* base;

    float baseDistance = 0;
private:
    float damageTimer = 0.0f;
    float damageIntervial = 1.0f;

    int damage = 5;
    float attackRange = 3.0f;
};

