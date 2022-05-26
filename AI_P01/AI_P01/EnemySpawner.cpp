#include "Enemy.h"
#include "Collider.h"
#include "Scene.h"
#include "EnemySpawner.h"
#include "GoblinWeak.h"
#include "GoblinNormal.h"
#include <stdlib.h>
#include <time.h>
#include "Player.h"
#include "Base.h"

EnemySpawner::EnemySpawner(sf::RenderWindow* _window, Scene* _scene, Base* _base)
{
	base = _base;
	window = _window;
	scene = _scene;
}

void EnemySpawner::Update(float _deltatime)
{
	bool gameover = true;
	for (std::vector<Player*>::iterator it = players.begin(); it < players.end(); it++)
	{
		Player* player = *it;
		if (!player->isDead)
		{
			gameover = false;
		}
	}
	if (gameover)
	{
		// trigger gameover
		scene->ChangeScene("Main_Menu");
		return;
	}
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

	//Spawns an enemy based on the random generated number
	srand(time(NULL));

	float randomNum = rand() % 10 + 1;
	Enemy* enemy = nullptr;

	if (randomNum < 5)
	{
		enemy = new GoblinWeak(window, scene, this, base);
	}

	else
	{
		enemy = new GoblinNormal(window, scene, this, base);
	}
	
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
