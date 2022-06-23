/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2022 Media Design School
File Name : GoblinHordeUI.h
Description : UI
Author : Devon Millar, James Charnley, Sam Chandler, Mahalon
Mail : devon.millar@mds.ac.nz, james.charnley@mds.ac.nz, samuel.chandler@mds.ac.nz, mahalon.Devoe@mds.ac.nz
**************************************************************************/

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
	class PlayerStats* GetPlayerStats(int _playerNum);

	//WaveManger.cpp will be able to display the breakTimer, current num of enemies and current wave onto the UI
	class WaveDisplay* GetWaveDisplay();

private:
	
	// pointer to playerStats and WaveDisplay
	class PlayerStats* player1Stats;
	class PlayerStats* player2Stats;
	class PlayerStats* player3Stats;
	class PlayerStats* player4Stats;

	class PlayerStats* playerStats[4];

	class WaveDisplay* waveDisplay;


};
