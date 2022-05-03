#pragma once
#include "GameObject_Circle.h"
#include "ITakeDamage.h"


class Character :
    public GameObject_Circle, public ITakeDamage
{

public:

    // Custom constructor: takes ref to sf::RenderWindow and Scene() class
    Character(sf::RenderWindow* _window, class Scene* _scene);

    // override update
    virtual void Update(float _deltatime) override;

    virtual void Move(sf::Vector2f _movement);

    virtual void TakeDamage(int _amount) override;
    virtual void TakeDamage(int _amount, Character* _player) override;

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

