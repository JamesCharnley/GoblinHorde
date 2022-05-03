#pragma once
#include "GameObject_Circle.h"
class EnemySpawner :
    public GameObject_Circle
{

public:

    EnemySpawner(sf::RenderWindow* _window, class Scene* _scene);

    virtual void Update(float _deltatime) override;

    virtual void Render() override;

    void EnemyDestroyed(class Enemy* _enemy);

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

