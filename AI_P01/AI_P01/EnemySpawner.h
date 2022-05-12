#pragma once
#include "GameObject_Circle.h"

class EnemySpawner :
    public GameObject_Circle
{

public:

    EnemySpawner(sf::RenderWindow* _window, class Scene* _scene);

    virtual void Update(float _deltatime) override;

    // Decreases currentEnemyCount variable. Called when Enemy is Destroyed/Killed
    void EnemyDestroyed(class Enemy* _enemy);

    // Add Player pointer ro players vector
    void AddPlayer(class Player* _player);

protected:

    int maximumEnemies = 2;
    int currentEnemyCount = 0;
    float spawnInterval = 3.0f;
    float spawnTimer = 0;

    void SpawnEnemy(sf::Vector2f _position);
    inline virtual void SpawnEnemy() { SpawnEnemy(sf::Vector2f(0.0f, 0.0f)); }

    std::vector<class Player*> players;
};

