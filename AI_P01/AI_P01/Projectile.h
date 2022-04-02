#pragma once
#include "GameObject_Circle.h"
class Projectile :
    public GameObject_Circle
{
public:

    Projectile(sf::RenderWindow* _window, class Scene* _scene, float _rotation);

    virtual void Update(float _deltatime) override;

protected:

    float speed = 50.0f;
    sf::Vector2f direction;
};

