#include "WaveManager.h"
#include "SpawnPoint.h"
#include "Scene.h"
#include "GoblinHordeUI.h"
#include "WaveDisplay.h"
#include <stdio.h>
#include <iostream>
#include <random>
#include "Player.h"

WaveManager::~WaveManager()
{
	srand(time(NULL));
	for (Spawn* & pointer : spawnPoints)
	{
		delete pointer;
		pointer = nullptr;
	}
}

//HACK: must pass dynamically alocated spawn
void WaveManager::AddSpawn(Spawn* _spawn)
{
	spawnPoints.push_back(_spawn);
}

void WaveManager::Update(float _deltatime)
{
	//Updates the wave display
	scene->GetUI()->getWaveDisplay()->UpdateWaveNum(currentWave);
	scene->GetUI()->getWaveDisplay()->UpdateEnemiesNum(currentEnemyCount);

	if (waveSpawnedEnemies >= totalWaveEnemies)
	{
		//stop spawning enemies, wait until all enemies are dead then call NextWave()
		if (currentEnemyCount == 0)
		{
			NextWave();
		}
		return;
	}

	//update the enemy spawner if wave break timer is less than 0
	if (waveBreakTimer > 0.0f)
	{
		scene->GetUI()->getWaveDisplay()->UpdateWaveTimer(waveBreakTimer);
		waveBreakTimer -= _deltatime;
	}
	else
	{
		EnemySpawner::Update(_deltatime);
	}
}

//spawn an enemy at a random spawn point
void WaveManager::SpawnEnemy()
{
	waveSpawnedEnemies++;
	EnemySpawner::SpawnEnemy(spawnPoints.at(rand() % spawnPoints.size())->GetSpawnPosition());	//TODO: test this with larger vector
}

//advance to next wave
void WaveManager::NextWave()
{
	currentWave++;
	waveSpawnedEnemies = 0;
	totalWaveEnemies += totalWaveEnemiesIncrement;
	maximumEnemies += maximumEnemiesIncrement;
	waveBreakTimer = waveBreakDuration;

	std::cout << "\n**Starting wave " << currentWave << "**\n";
	std::cout << "Wave enemies " << totalWaveEnemies << "\n";
	std::cout << "Max on screen enemies " << maximumEnemies << "\n";
	std::cout << "Spawn interval " << spawnInterval << "\n\n";

	
	
	for (std::vector<Player*>::iterator it = players.begin(); it < players.end(); it++)
	{
		Player* player = *it;
		if (player->isDead)
		{
			player->Respawn();
		}
	}
}  
