#pragma once
#include "EnemySpawner.h"

class Spawn;

class WaveManager : public EnemySpawner
{
public:
	WaveManager(sf::RenderWindow* _window, Scene* _scene) : EnemySpawner(_window, _scene) {};
	~WaveManager();
	void AddSpawn(Spawn* _spawn);
	virtual void Update(float _deltatime) override;

protected:
	void SpawnEnemy();

private:

	std::vector<Spawn*> spawnPoints;
	void NextWave();
	float waveBreakDuration = 3.0f;
	float waveBreakTimer = 0.0f;

	int currentWave = 0;
	int waveSpawnedEnemies= 0;

	//linear for now, shold look into feeding the wave number into a function for these values later
	int totalWaveEnemies = 4;
	int totalWaveEnemiesIncrement = 3;
	int maximumEnemiesIncrement = 2;
};

