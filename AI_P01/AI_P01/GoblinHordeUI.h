#pragma once
#include <vector>
#include "SFML\Graphics.hpp"
#include <iostream>

class GoblinHordeUI
{
public:
	GoblinHordeUI();
	~GoblinHordeUI();

	//Renders both player1, player2 stats and the wave display
	void Render(sf::RenderWindow* window);

	//Player.cpp will be able to display the health, ammo and gold onto the UI
	class PlayerStats* getPlayer1Stats();
	class PlayerStats* getPlayer2Stats();

	//WaveManger.cpp will be able to display the breakTimer, current num of enemies and current wave onto the UI
	class WaveDisplay* getWaveDisplay();

private:
	
	// pointer to playerStats and WaveDisplay
	class PlayerStats* player1Stats;
	class PlayerStats* player2Stats;
	class WaveDisplay* waveDisplay;

};
