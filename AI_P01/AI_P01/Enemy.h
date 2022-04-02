#pragma once
#include "Character.h"
class Enemy :
    public Character
{
public:

    Enemy(sf::RenderWindow* _window, Scene* _scene);
    Enemy(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner);

    virtual void Update(float _deltatime) override;

    void AddPlayer(class Player* _player);

    virtual void Destroy() override;

protected:

    std::vector<class Player*> players;
    class Player* closestPlayer = nullptr;
    class EnemySpawner* spawner = nullptr;
};

