#pragma once
#include "Character.h"
#include <SFML/Audio.hpp>

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

    sf::Sound hitSFX;
    sf::SoundBuffer buffer;
 
};

