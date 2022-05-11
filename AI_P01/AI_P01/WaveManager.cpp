#include "WaveManager.h"
#include "SpawnPoint.h"
#include "Scene.h"
#include "GoblinHordeUI.h"
#include <stdio.h>
#include <iostream>

WaveManager::~WaveManager()
{
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
	scene->getUI()->setCurrentWave(currentWave);
	scene->getUI()->setNumberOfEnemies(currentEnemyCount);

	if (waveSpawnedEnemies >= totalWaveEnemies)
	{
		//stop spawning enemies, wait until all enemies are dead then call NextWave()
		if (currentEnemyCount == 0)
		{
			NextWave();
		}
		return;
	}

	if (waveBreakTimer > 0.0f)
	{
		scene->getUI()->setWaveTimer(waveBreakTimer);
		waveBreakTimer -= _deltatime;
	}
	else
	{
		EnemySpawner::Update(_deltatime);
	}
}

void WaveManager::SpawnEnemy()
{
	waveSpawnedEnemies++;
	EnemySpawner::SpawnEnemy(spawnPoints.front()->GetSpawnPosition());	//HACK: should pick a random spawn point to use
}

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
}
