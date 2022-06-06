/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : EnemySpawner.h
Description : Implementation to spawn enemies at a point
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectCircle.h"

class EnemySpawner :
    public GameObjectCircle
{

public:

    EnemySpawner(sf::RenderWindow* _window, class Scene* _scene, class Base* _base);

    virtual void Update(float _deltatime) override;

    // Decreases currentEnemyCount variable. Called when Enemy is Destroyed/Killed
    void EnemyDestroyed(class Enemy* _enemy);

    // Add Player pointer ro players vector
    void AddPlayer(class Player* _player);

protected:

    class Base* base;

    int maximumEnemies = 2;
    int currentEnemyCount = 0;
    float spawnInterval = 2.5f;
    float spawnTimer = 0;

    void SpawnEnemy(sf::Vector2f _position, float _health = 20.0f, float _damage = 5.0f);
    inline virtual void SpawnEnemy() { SpawnEnemy(sf::Vector2f(0.0f, 0.0f)); }

    std::vector<class Player*> players;
};

