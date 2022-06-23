#include "WaveManager.h"
#include "SpawnPoint.h"
#include "Scene.h"
#include "GoblinHordeUI.h"
#include "WaveDisplay.h"
#include <stdio.h>
#include <iostream>
#include <random>
#include "Player.h"
#include "Utility.h"

WaveManager::WaveManager(sf::RenderWindow* _window, Scene* _scene, Base* _base, int _playerCount, float _waveBreakTime) 
	: EnemySpawner(_window, _scene, _base), DIFFICULTY_MODIFIER((float)_playerCount)
{
	//scale difficulty by player count
	baseTotalWaveEnemies *= DIFFICULTY_MODIFIER;
	maximumEnemiesIncrement *= DIFFICULTY_MODIFIER;
	waveDmg = baseWaveDmg;
	waveHealth = baseWaveHealth;
	totalWaveEnemies = baseTotalWaveEnemies;
	waveBreakDuration = _waveBreakTime;
}

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
	//updates the wave display
	scene->GetUI()->GetWaveDisplay()->UpdateWaveNum(currentWave + 1);
	scene->GetUI()->GetWaveDisplay()->UpdateEnemiesNum(totalWaveEnemies - waveSpawnedEnemies + currentEnemyCount);

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
		scene->GetUI()->GetWaveDisplay()->UpdateWaveTimer(waveBreakTimer);
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
	EnemySpawner::SpawnEnemy(spawnPoints.at(rand() % spawnPoints.size())->GetSpawnPosition(), waveHealth, waveDmg);
}

//advance to next wave
void WaveManager::NextWave()
{
	currentWave++;
	waveSpawnedEnemies = 0;
	maximumEnemies += maximumEnemiesIncrement;
	waveBreakTimer = waveBreakDuration;
	totalWaveEnemies = floor((baseTotalWaveEnemies + (currentWave * 1.5f)) * DIFFICULTY_MODIFIER);
	waveHealth = baseWaveHealth + (currentWave * 3.5f);
	waveDmg = baseWaveDmg + (log(((currentWave / 10.0f) + 1)) * 10.0f);
	spawnInterval *= 0.9f;

	if (Utils::IS_DEBUG)
	{
		std::cout << "\n**Starting wave " << currentWave + 1 << "**\n";
		std::cout << "Wave enemies " << totalWaveEnemies << "\n";
		std::cout << "Max on screen enemies " << maximumEnemies << "\n";
		std::cout << "Spawn interval " << spawnInterval << "\n";
		std::cout << "Enemy health " << waveHealth << "\n";
		std::cout << "Enemy damage " << waveDmg << "\n\n";
	}
	
	for (std::vector<Player*>::iterator it = players.begin(); it < players.end(); it++)
	{
		Player* player = *it;
		if (player->isDead)
		{
			player->Respawn();
		}
		else
		{
			player->ResetHealth();
		}
	}
}  
