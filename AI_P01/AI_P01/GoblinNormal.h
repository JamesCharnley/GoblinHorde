/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GoblinNormal.h
Description : A normal goblin enemy variant
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Enemy.h"

class GoblinNormal : public Enemy
{
public:
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene, class Base* _base, float _health = 20.0f, float _damage = 5.0f);
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base, float _health = 20.0f, float _damage = 5.0f);
};

