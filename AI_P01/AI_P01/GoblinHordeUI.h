#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include <iostream>

//UI takes in data from current scene and display it through a text
class GoblinHordeUI
{
public:
	GoblinHordeUI(sf::RenderWindow* window);
	~GoblinHordeUI();

	void setCurrentWave(int currWave);
	void setNumberOfEnemies(int numEnemies);
	void setWaveTimer(int timer);

	void setPlayer1Stats(int gold);
	void setPlayer2Stats(int gold);

	void Render(sf::RenderWindow* window);

private:
	class GameText* m_WaveText = nullptr;
	class GameText* m_WaveNum = nullptr;
	class GameText* m_EnemyText = nullptr;
	class GameText* m_EnemyNum = nullptr;

	class GameText* m_player1Text = nullptr;
	class GameText* m_player1Stats = nullptr;
	class GameText* m_player2Text = nullptr;
	class GameText* m_player2Stats = nullptr;

	class GameText* m_waveTimer = nullptr;

	//std::vector<class GameText*> m_Texts;
};
