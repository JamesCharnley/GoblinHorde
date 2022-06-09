#include "GoblinHordeUI.h"
#include "GameText.h"
#include "Scene.h"
#include "Player.h"
#include "PlayerStats.h"
#include "WaveDisplay.h"
#include "Utility.h"

GoblinHordeUI::GoblinHordeUI()
{	
	player1Stats = new PlayerStats(sf::Vector2f(100, 15));
	player2Stats = new PlayerStats(sf::Vector2f(Utils::WINDOW_X - 210, 15));
	player3Stats = new PlayerStats(sf::Vector2f(100, Utils::WINDOW_Y - 120));
	player4Stats = new PlayerStats(sf::Vector2f(Utils::WINDOW_X - 210, Utils::WINDOW_Y - 120));
	waveDisplay = new WaveDisplay(sf::Vector2f(800, 15));
}

GoblinHordeUI::~GoblinHordeUI()
{
	delete player1Stats;
	delete player2Stats;
	delete waveDisplay;

	player1Stats = nullptr;
	player2Stats = nullptr;
	player3Stats = nullptr;
	player4Stats = nullptr;
	waveDisplay = nullptr;
}

//Renders all the game texts
void GoblinHordeUI::Render(sf::RenderWindow* window)
{
	player1Stats->Render(window);
	player2Stats->Render(window);
	player3Stats->Render(window);
	player4Stats->Render(window);
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

PlayerStats* GoblinHordeUI::getPlayer3Stats()
{
	return player3Stats;
}

PlayerStats* GoblinHordeUI::getPlayer4Stats()
{
	return player4Stats;
}

//Wave manage class will be able to display the breakTimer, current num of enemies and current wave onto the UI
WaveDisplay* GoblinHordeUI::getWaveDisplay()
{
	return waveDisplay;
}
