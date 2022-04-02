#pragma once
#include "GameObject_Circle.h"
class Projectile :
    public GameObject_Circle
{
public:

    Projectile(sf::RenderWindow* _window, class Scene* _scene, float _rotation, GameObject* _owner);

    virtual void Update(float _deltatime) override;

    virtual void OnCollision(GameObject* _other) override;

protected:

    int damage = 20;
    float speed = 600.0f;
    sf::Vector2f direction;
};

