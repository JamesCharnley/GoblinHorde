#include "GoblinHordeUI.h"
#include "GameText.h"
#include "Scene.h"
#include "Player.h"
#include "PlayerStats.h"
#include "WaveDisplay.h"

GoblinHordeUI::GoblinHordeUI()
{
	player1Stats = new PlayerStats(sf::Vector2f(0, 0));
	player2Stats = new PlayerStats(sf::Vector2f(1550, 0));
	waveDisplay = new WaveDisplay(sf::Vector2f(800, 0));
}

GoblinHordeUI::~GoblinHordeUI()
{
	delete player1Stats;
	delete player2Stats;
	delete waveDisplay;

	player1Stats = nullptr;
	player2Stats = nullptr;
	waveDisplay = nullptr;
}

//Renders all the game texts
void GoblinHordeUI::Render(sf::RenderWindow* window)
{
	player1Stats->Render(window);
	player2Stats->Render(window);
	waveDisplay->Render(window);
}

//Player class will be able to display there gold, health and ammo onto the UI
PlayerStats* GoblinHordeUI::getPlayer1Stats()
{
	return player1Stats;
}

PlayerStats* GoblinHordeUI::getPlayer2Stats()
{
	return player2Stats;
}

//Wave manage class will be able to display the breakTimer, current num of enemies and current wave onto the UI
WaveDisplay* GoblinHordeUI::getWaveDisplay()
{
	return waveDisplay;
}
