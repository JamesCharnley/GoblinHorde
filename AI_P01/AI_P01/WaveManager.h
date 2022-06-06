/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : WaveManager.h
Description : Controller for a EnemySpawner that spawns enemies at passed in spawn locations
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

#pragma once
#include "EnemySpawner.h"

class Spawn;

class WaveManager : public EnemySpawner
{
public:
	WaveManager(sf::RenderWindow* _window, Scene* _scene, class Base* _base, int _playerCount = 1);
	~WaveManager();

	//ads a spawn pointer to spawnPoints vector
	void AddSpawn(Spawn* _pSpawn);

	virtual void Update(float _deltatime) override;

protected:
	void SpawnEnemy();

private:

	//updating variables for the next wave of enemies
	void NextWave();

	std::vector<Spawn*> spawnPoints;
	float waveBreakDuration = 10.0f;
	float waveBreakTimer = 0.0f;

	int currentWave = 0;
	int waveSpawnedEnemies= 0;

	int baseTotalWaveEnemies = 4;
	int totalWaveEnemies;
	float maximumEnemiesIncrement = 1.5;

	float baseWaveDmg = 5.0f;
	float baseWaveHealth = 20.0f;
	float waveDmg = 5.0f;
	float waveHealth = 20.0f;

	const float DIFFICULTY_MODIFIER;

};

