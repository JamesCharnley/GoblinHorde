/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2021 Media Design School
File Name : GoblinWeak.h
Description : A weak goblin enemy variant
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "Enemy.h"

class GoblinWeak : public Enemy
{
public:
	GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class Base* _base);
	GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base);
};

