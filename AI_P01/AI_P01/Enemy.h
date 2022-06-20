/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : Enemy.h
Description : Enemy to attack the player and base
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Character.h"
#include <SFML/Audio.hpp>

class Enemy :
    public Character
{
public:

    Enemy(sf::RenderWindow* _window, Scene* _scene, class Base* _base, float _health = 20.0f, float _damage = 5.0f);
    Enemy(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base, float _health = 20.0f, float _damage = 5.0f);

    virtual void Update(float _deltatime) override;

    void AddPlayer(class Player* _player);

    virtual void TakeDamage(int _amount, Character* _player) override;

    virtual void Destroy() override;

protected:

    std::vector<class Player*> players;
    class Player* closestPlayer = nullptr;
    class EnemySpawner* spawner = nullptr;

    int goldReward = 35;

    class Base* base;

    float baseDistance = 0;
private:
    float damageTimer = 0.0f;
    float damageIntervial = 1.0f;

    float damage = 5.0f;
    float attackRange = 3.0f;

    sf::Sound hitSFX;
    sf::Sound goblinDieSFX;
    sf::SoundBuffer buffer;

    sf::Sound baseDamageSFX;
    sf::SoundBuffer baseDamageSFXBuffer;
 
};

