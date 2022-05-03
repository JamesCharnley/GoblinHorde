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
	else
	{
		spawnTimer -= _deltatime;
	}
}

void EnemySpawner::Render()
{
}

void EnemySpawner::EnemyDestroyed(Enemy* _enemy)
{
	currentEnemyCount--;
}

void EnemySpawner::AddPlayer(Player* _player)
{
	players.push_back(_player);
}

void EnemySpawner::SpawnEnemy()
{
	Enemy* enemy = new Enemy(window, scene, this);
	enemy->SetRadius(50.0f);
	enemy->SetCollisionRadius(50.f);
	enemy->GetCollider()->SetCollisionType(ECollisionType::Block);

	for (int i = 0; i < (int)players.size(); i++)
	{
		enemy->AddPlayer(players[i]);
	}
	scene->AddSceneObject(enemy);
	currentEnemyCount++;
}
