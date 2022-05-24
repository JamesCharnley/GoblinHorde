#pragma once
#include "Enemy.h"

class GoblinNormal : public Enemy
{
public:
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene);
	GoblinNormal(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner);
};

