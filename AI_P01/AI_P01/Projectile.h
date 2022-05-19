#pragma once
#include "GameObject_Circle.h"
class Projectile :
    public GameObject_Circle
{
public:

    Projectile(sf::RenderWindow* _window, class Scene* _scene, float _rotation, GameObject* _owner, float _damage = 20.0f, float _speed = 600.0f);

    virtual void Update(float _deltatime) override;

    virtual void OnCollision(GameObject* _other) override;

    void SetDontDamagePlayers() { dontDamagePlayers = true; };
    void SetDontDamageEnemies() { dontDamageEnemies = true; };

protected:

    int damage = 20;
    float speed = 600.0f;
    sf::Vector2f direction;
    bool dontDamagePlayers = false;
    bool dontDamageEnemies = false;

    class Character* owningCharacter = nullptr;
};

