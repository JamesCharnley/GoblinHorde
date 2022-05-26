#pragma once
#include "Enemy.h"

class GoblinNormal : public Enemy
{
public:
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene, class Base* _base);
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base);
};

