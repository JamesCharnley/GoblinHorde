/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : Projectile.h
Description : A projectile that moves in a staight line, instances created with a Weapon
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "GameObjectCircle.h"
class Projectile :
    public GameObjectCircle
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

