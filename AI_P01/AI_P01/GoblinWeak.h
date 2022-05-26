#pragma once
#include "Enemy.h"

class GoblinWeak : public Enemy
{
public:
	GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class Base* _base);
	GoblinWeak(sf::RenderWindow* _window, Scene* _scene, class EnemySpawner* _spawner, class Base* _base);
};

