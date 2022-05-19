#include "Enemy.h"
#include "Collider.h"
#include "Scene.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(sf::RenderWindow* _window, Scene* _scene)
{
	window = _window;
	scene = _scene;
}

void EnemySpawner::Update(float _deltatime)
{
	if (spawnTimer <= 0)
	{
		if (currentEnemyCount < maximumEnemies)
		{
			SpawnEnemy();
			spawnTimer = spawnInterval;
		}
	}
	else if (currentEnemyCount < maximumEnemies)
	{
		spawnTimer -= _deltatime;
	}
}

void EnemySpawner::EnemyDestroyed(Enemy* _enemy)
{
	currentEnemyCount--;
}

void EnemySpawner::AddPlayer(Player* _player)
{
	players.push_back(_player);
}

void EnemySpawner::SpawnEnemy(sf::Vector2f _position)
{
	Enemy* enemy = new Enemy(window, scene, this);
	enemy->SetRadius(25.0f);
	enemy->SetCollisionRadius(25.0f);
	enemy->GetCollider()->SetCollisionType(ECollisionType::Block);
	enemy->SetPosition(_position);

	for (int i = 0; i < (int)players.size(); i++)
	{
		enemy->AddPlayer(players[i]);
	}
	scene->AddSceneObject(enemy);
	currentEnemyCount++;
}
